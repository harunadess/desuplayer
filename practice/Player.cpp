#include "Player.h"

#include <Windows.h>
#include <iostream>
#include <string>

using std::wcout;
using std::cin;
using std::flush;
using std::endl;

Player::Player(MpControls& mpControls, IPC* ipc)
	:m_mpControls(&mpControls), m_ipc(ipc)
{
}


Player::~Player()
{
	delete m_extraDriverData;
}

void Player::ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
	if (result != FMOD_OK)
	{
		std::wstring str = L"FMOD error! (";
		str += (int)result;
		str += L")";
		str += (const wchar_t*)FMOD_ErrorString(result);
		str += L"\n";

		m_ipc->writeToPipe(str);
	}
}

//int Player::play(std::string filePath)
void Player::play(PlayDeets& playDeets)
{
	//Initialize
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED); //initialize windows api

	//Create stream for the file we want to use
	initialize();
 	createStream(playDeets.filePath.c_str());

	//Actually play the file
	playSound();
	m_channel->setVolume(m_currentVolume);
	int exitCode = corePlayLoop();

	//Shut down once file finishes
	soundRelease();
	systemClose();
	systemRelease();

	CoUninitialize(); //uninitialize the stream

	playDeets.exitCode = exitCode;
}

void Player::initialize()
{	   
	//Create a System object and initialize
	systemCreate(); 
	getFmodVersion();
	checkFmodVersion();
	systemInitialize();

	m_io = new PlayerIOHandler();
}

void Player::systemCreate()
{
	m_result = FMOD::System_Create(&m_system);
	ERRCHECK_fn(m_result, __FILE__, __LINE__);


	// only do this if it's a m4a file...

	/*FMOD_CODEC_DESCRIPTION *m4a = FMODGetCodecDescription();
	unsigned int* handle = 0;

	m_result = m_system->registerCodec(m4a, handle, 0);
	ERRCHECK_fn(m_result, __FILE__, __LINE__);*/
}

void Player::checkFmodVersion()
{
	//ensure library version matches files
	if (m_version < FMOD_VERSION)
	{
		m_ipc->writeToPipe(L"FMOD lib version doesn't match header version");
		exit(1);
	}
}

void Player::getFmodVersion()
{
	m_result = m_system->getVersion(&m_version);
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

void Player::systemInitialize()
{
	//initialize system with driver data
	m_result = m_system->init(32, FMOD_INIT_NORMAL, m_extraDriverData);
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

void Player::createStream(const char* songLocation)
{
	//create stream to play
	m_result = m_system->createStream(songLocation, FMOD_LOOP_OFF | FMOD_2D, 0, &m_sound);
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

void Player::playSound()
{
	//actual call to play sound
	m_result = m_system->playSound(m_sound, 0, false, &m_channel);
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

int Player::corePlayLoop()
{   
	int exitCode = 0;
	
	while (true)
	{
		unsigned int ms = 0;
		unsigned int lenms = 0;
		bool playing = false; 
		bool paused = false;

		systemUpdate();

		//check if there is keyboard input, if there is, do some stuff
		// if (_kbhit())
		checkForInput(exitCode);

		if (exitCode != 0)
			break;

		{
			if (m_channel)
			{
				checkIsPlaying(playing);
				checkIsPaused(paused);
				getSeekPosition(ms);
				getLength(lenms);

				if ((!playing && !paused) && (ms == 0))
				{
					return exitCode;
				}
			}
		}

		//sleep so we're not ramming the cpu by running the loop as fast as possible
		Sleep(50);
	}

	return exitCode;
}

//post init update function
void Player::systemUpdate()
{
	m_result = m_system->update();
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

void Player::checkForInput(int& exitCode)
{
	// can't use this anymore - _getch()...
	//m_io->processInput();

	/*if (m_io->isPauseKey())
	{
		bool paused;
		m_result = m_channel->getPaused(&paused);
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
		m_result = m_channel->setPaused(!paused);
	}
	if (m_io->isSkipForwardKey())
	{
		exitCode = 2;
		return;
	}
	if (m_io->isSkipBackKey())
	{
		exitCode = 3;
		return;
	}*/

	if (m_mpControls->pause)
	{
		bool paused;
		m_result = m_channel->getPaused(&paused);
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
		m_result = m_channel->setPaused(!paused);
		m_mpControls->pause.store(false);
		
		exitCode = NORMAL;
	}
	else if (m_mpControls->stop)
	{
		exitCode = STOP;
		m_mpControls->stop.store(false);
		m_mpControls->pause.store(true); // we don't want to immediately play after stopping and continuing
	}
	else if (m_mpControls->next)
	{
		exitCode = NEXT;
		m_mpControls->next.store(false);
	}
	else if (m_mpControls->prev)
	{
		exitCode = PREVIOUS;
		m_mpControls->prev.store(false);
	}
	else if (m_mpControls->exit)
	{
		exitCode = EXIT;
		m_mpControls->exit.store(false);
	}
	else if (m_mpControls->vol_up)
	{
		getVolume(m_currentVolume);

		if (m_currentVolume < MAX_VOLUME)
		{
			m_currentVolume += VOLUME_INCREMENT;
			setVolume(m_currentVolume);

			std::wstring str = L"Set volume to ";
			str += std::to_wstring((int)(m_currentVolume * 100));
			str += L"%";

			m_ipc->writeToPipe(str);
			m_mpControls->vol_up.store(false);
		}
		exitCode = NORMAL;
	}
	else if (m_mpControls->vol_down)
	{
		getVolume(m_currentVolume);

		if (m_currentVolume > MIN_VOLUME)
		{
			m_currentVolume -= VOLUME_INCREMENT;
			setVolume(m_currentVolume);

			std::wstring str = L"Set volume to ";
			str += std::to_wstring((int)(m_currentVolume * 100));
			str += L"%";

			m_ipc->writeToPipe(str);
			m_mpControls->vol_down.store(false);
		}
		exitCode = NORMAL;
	}
}

void Player::checkIsPlaying(bool& playing)
{
	m_result = m_channel->isPlaying(&playing);
	if ((m_result != FMOD_OK) && (m_result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
	}
}

void Player::checkIsPaused(bool& paused)
{
	m_result = m_channel->getPaused(&paused);
	if ((m_result != FMOD_OK) && (m_result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
	}
}

void Player::getVolume(float& volume)
{
	m_result = m_channel->getVolume(&volume);
	if ((m_result != FMOD_OK) && (m_result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
	}
}

void Player::setVolume(float& volume)
{
	m_result = m_channel->setVolume(volume);
	if ((m_result != FMOD_OK) && (m_result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
	}
}

void Player::getSeekPosition(unsigned int& ms)
{
	m_result = m_channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	if ((m_result != FMOD_OK) && (m_result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
	}
}

void Player::getLength(unsigned int& lenms)
{
	m_result = m_sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
	if ((m_result != FMOD_OK) && (m_result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(m_result, __FILE__, __LINE__);
	}
}

//release parent sound, not the one that was retrieved with getSubSound
void Player::soundRelease()
{
	m_result = m_sound->release();
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

//close system as we are done playing
void Player::systemClose()
{
	m_result = m_system->close();
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}

//release system now we are finished
void Player::systemRelease()
{
	m_result = m_system->release();
	ERRCHECK_fn(m_result, __FILE__, __LINE__);
}
