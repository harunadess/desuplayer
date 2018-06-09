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
}

void Player::systemCreate()
{
	result = FMOD::System_Create(&system);
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::checkFmodVersion()
{
	if (version < FMOD_VERSION) //ensure library version matches files
	{
		cout << ("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION) << endl;
		exit(0);
	}
}

void Player::getFmodVersion()
{
	result = system->getVersion(&version);
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::systemInitialize()
{
	result = system->init(32, FMOD_INIT_NORMAL, extraDriverData); //initialize system with driver data
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::createStream(const char *songLocation)
{
	//result = system->createStream("../media/sound.mp3", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound); //create stream to play
	result = system->createStream(songLocation, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound); //create stream to play
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::playSound()
{
	result = system->playSound(sound, 0, false, &channel); //actual call to play sound
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::corePlayLoop() //currently plays song in repeat
{
	char c = '/'; //control character
	cout << "Use 'p' to pause, 'e' to exit.";
	
	do //control for main play loop
	{
		//ToDo: create input handler to deal with input
		cin >> c; //use this to get user input for controlling the player: currently a char, but should probably be a key press.
		if (c == 'p')
		{
			bool paused;
			result = channel->getPaused(&paused);
			ERRCHECK_fn(result, __FILE__, __LINE__);
			result = channel->setPaused(!paused);
		}

		this->systemUpdate();

		{
			unsigned int ms = 0; //not used - potentially needed to display "time left"
			unsigned int lenms = 0; //not used - as above ^
			bool         playing = false; //control flag for playing
			bool         paused = false; //control flag for paused

			if (channel)
			{
				this->isPlaying(playing);

				this->isPaused(paused);

				this->getPosition(ms);
			}
			cout << (paused ? "Paused " : playing ? "Playing" : "Stopped") << endl;
		} //playing block

		Sleep(50); //sleep so we're not ramming the cpu by running the loop as fast as possbile
	} while (c != 'e'); //exit condition
}

void Player::systemUpdate()
{
	result = system->update(); //post init update function
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

bool Player::isPlaying(bool playing)
{
	result = channel->isPlaying(&playing);
	if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result, __FILE__, __LINE__);
	}
	return playing;
}

bool Player::isPaused(bool paused)
{
	result = channel->getPaused(&paused);
	if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result, __FILE__, __LINE__);
	}
	return paused;
}

void Player::getPosition(unsigned int ms)
{
	result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
	{
		ERRCHECK_fn(result, __FILE__, __LINE__);
	}
}

void Player::soundRelease()
{
	result = sound->release(); //release parent, not the sound that was retrieved with getSubSound
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::systemClose()
{
	result = system->close(); //close system as we are done playing
	ERRCHECK_fn(result, __FILE__, __LINE__);
}

void Player::systemRelease()
{
	result = system->release(); //release system now we are finished
	ERRCHECK_fn(result, __FILE__, __LINE__);

}
