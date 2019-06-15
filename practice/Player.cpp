#include "Player.h"

#include <Windows.h>
#include <iostream>
#include <string>

using std::wcout;
using std::cin;
using std::flush;
using std::endl;

#define MAX_PATH 260

Player::Player()
{
}


Player::~Player()
{
	delete this->extraDriverData_;
}

//void(*Common_Private_Error)(FMOD_RESULT, const char *, int);
void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line) //error check function - not sure how necessary this is, but eh.
{
	if (result != FMOD_OK)
	{
		/*if (Common_Private_Error)
		{
			Common_Private_Error(result, file, line);
		}*/
		wprintf(L"FMOD error! (%d) %hs\n", result, FMOD_ErrorString(result));
	}
}

void Player::play(string filePath)
{
	//Initialize
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED); //initialize windows api

	this->initialize();
 	this->createStream(filePath.c_str());

	//wcout << "playing: " << filePath.c_str() << endl;
	//Playing
	this->playSound();
	this->corePlayLoop();

	//Shut down 
	this->soundRelease();
	this->systemClose();
	this->systemRelease();

	CoUninitialize(); //uninitialse the stream
}

void Player::initialize()
{	   
	this->systemCreate(); //Create a System object and initialize
	this->getFmodVersion();
	this->checkFmodVersion();
	this->systemInitialize();
	this->io_ = new PlayerIOHandler();
}

void Player::systemCreate()
{
	result_ = FMOD::System_Create(&system_);
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::checkFmodVersion()
{
	if (version_ < FMOD_VERSION) //ensure library version matches files
	{
		wcout << ("FMOD lib version %08x doesn't match header version %08x", version_, FMOD_VERSION) << endl;
		exit(1);
	}
}

void Player::getFmodVersion()
{
	result_ = system_->getVersion(&version_);
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::systemInitialize()
{
	result_ = system_->init(32, FMOD_INIT_NORMAL, extraDriverData_); //initialize system with driver data
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::createStream(const char* songLocation)
{
	//result_ = system_->createStream(songLocation, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound_); //create stream to play
	result_ = system_->createStream(songLocation, FMOD_LOOP_OFF | FMOD_2D, 0, &sound_); //create stream to play
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::playSound()
{
	result_ = system_->playSound(sound_, 0, false, &channel_); //actual call to play sound
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::corePlayLoop() //currently plays song in repeat
{   
	this->io_->outputText(L"Press Spacebar to Pause/Resume, press Escape to stop.");
	
	while (true)
	{
		unsigned int ms = 0;
		unsigned int lenms = 0;
		bool         playing = false; //control flag for playing
		bool         paused = false; //control flag for paused

		this->systemUpdate();

		if (_kbhit()) //check if there is keyboard input, if there is, do some stuff
		{
			this->io_->processInput();
			if (this->io_->isPauseKey())
			{
				bool paused;
				result_ = channel_->getPaused(&paused);
				ERRCHECK_fn(result_, __FILE__, __LINE__);
				result_ = channel_->setPaused(!paused);
			}
			if (this->io_->isExitKey())
				break;
		}

		{
			if (channel_)
			{
				this->checkIsPlaying(playing);
				this->checkIsPaused(paused);
				this->getSeekPosition(ms);
				this->getLength(lenms);

				if ((!playing && !paused) && (ms == 0))
					return;
			}
		}

		Sleep(50); //sleep so we're not ramming the cpu by running the loop as fast as possible
	}
}

void Player::systemUpdate()
{
	result_ = system_->update(); //post init update function
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::checkIsPlaying(bool& playing)
{
	result_ = channel_->isPlaying(&playing);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
}

void Player::checkIsPaused(bool& paused)
{
	result_ = channel_->getPaused(&paused);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
}

void Player::getSeekPosition(unsigned int& ms)
{
	result_ = channel_->getPosition(&ms, FMOD_TIMEUNIT_MS);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
}

void Player::getLength(unsigned int& lenms)
{
	result_ = sound_->getLength(&lenms, FMOD_TIMEUNIT_MS);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
}

void Player::soundRelease()
{
	result_ = sound_->release(); //release parent, not the sound that was retrieved with getSubSound
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::systemClose()
{
	result_ = system_->close(); //close system as we are done playing
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::systemRelease()
{
	result_ = system_->release(); //release system now we are finished
	ERRCHECK_fn(result_, __FILE__, __LINE__);

}
