#include "Player.h"

#include <Windows.h>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::flush;
using std::endl;


Player::Player()
{
}


Player::~Player()
{
	delete this->extraDriverData_;
}

void(*Common_Private_Error)(FMOD_RESULT, const char *, int);
void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line) //error check function - not sure how necessary this is, but eh.
{
	if (result != FMOD_OK)
	{
		if (Common_Private_Error)
		{
			Common_Private_Error(result, file, line);
		}
		cout << ("%s(%d): FMOD error %d - %s", file, line, result) << endl;
	}
}

void Player::play(Song* song)
{
	//Initialize
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED); //initialize windows api

	this->initialize();
	this->createStream(song->getFilePath());
	
	//Playing
	this->playSound();
	cout << "========================================================================" << endl;
	cout << "Playing " << song->getFilePath() << endl << endl; //print what is being played
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
	this->io_ = new PlayerIOHandlerr();
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
		cout << ("FMOD lib version %08x doesn't match header version %08x", version_, FMOD_VERSION) << endl;
		exit(0);
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

void Player::createStream(const char *songLocation)
{
	result_ = system_->createStream(songLocation, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound_); //create stream to play
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::playSound()
{
	result_ = system_->playSound(sound_, 0, false, &channel_); //actual call to play sound
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

void Player::corePlayLoop() //currently plays song in repeat
{   
	//todo: modify current play loop with IOHandler to control operation 

	//char c = '/'; //control character
	//cout << "Use 'p' to pause, 'e' to exit." << endl;
	this->io_->outputText("Use 'P' to Pause, 'Q' to exit.");
	
	while (true)
	{
		//cin >> c; //use this to get user input for controlling the player: currently a char, but should probably be a key press.
		this->io_->processInput();
		if (this->io_->isPauseKey())
		{
			bool paused;
			result_ = channel_->getPaused(&paused);
			ERRCHECK_fn(result_, __FILE__, __LINE__);
			result_ = channel_->setPaused(!paused);
		}

		this->systemUpdate();

		{
			unsigned int ms = 0;
			unsigned int lenms = 0;
			bool         playing = false; //control flag for playing
			bool         paused = false; //control flag for paused

			if (channel_)
			{
				this->checkIsPlaying(playing);
				this->checkIsPaused(paused);
				this->getSeekPosition(ms);
			}
			if (paused)
			{
				//cout << "Paused" << endl;
				this->io_->outputText("Paused");
			}
			else if (playing)
			{
				/*cout << "Playing: " << (ms * 1000) << "s" << endl;*/
				this->io_->outputTextInline("Playing " + (ms * 1000));
				this->io_->outputTextInline("s");
				this->io_->outputNewline();
			}
			else
			{
				//cout << "Stopped" << endl;
				this->io_->outputText("Stopped");
			}
		}

		Sleep(50); //sleep so we're not ramming the cpu by running the loop as fast as possible

		if (this->io_->isExitKey())
			break;
	}
}

void Player::systemUpdate()
{
	result_ = system_->update(); //post init update function
	ERRCHECK_fn(result_, __FILE__, __LINE__);
}

bool Player::checkIsPlaying(bool& playing)
{
	result_ = channel_->isPlaying(&playing);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
	return playing;
}

bool Player::checkIsPaused(bool& paused)
{
	result_ = channel_->getPaused(&paused);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
	return paused;
}

unsigned int Player::getSeekPosition(unsigned int ms)
{
	result_ = channel_->getPosition(&ms, FMOD_TIMEUNIT_MS);
	if ((result_ != FMOD_OK) && (result_ != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result_, __FILE__, __LINE__);
	}
	return ms;
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
