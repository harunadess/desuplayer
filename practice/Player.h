#ifndef PLAYER_H
#define PLAYER_H

#include "ThirdParty/lowlevel/inc/fmod.hpp"
#include "ThirdParty/lowlevel/inc/fmod_common.h"
#include "playerIOHandler.h"

class Player
{
public:
	Player();
	~Player();

	void play(std::string filePath);
	void checkIsPlaying(bool& playing);
	void checkIsPaused(bool& paused);
	void getSeekPosition(unsigned int& ms);
	void getLength(unsigned int& ms);

private:
	//system obj: will play sound
	FMOD::System* system_;
	//actual audio
	FMOD::Sound* sound_;
	//current audio channel
	FMOD::Channel* channel_ = 0;
	//error checking result for most actions taken by FMOD
	FMOD_RESULT result_;
	//version of fmod being used
	unsigned int version_;
	//extra driver data of audio subsystem
	void* extraDriverData_ = 0;	
	PlayerIOHandler *io_;

	void initialize();
	void systemCreate();
	void getFmodVersion();
	void checkFmodVersion();
	void systemInitialize();
	void createStream(const char* songLocation);
	void playSound();
	void corePlayLoop();
	void systemUpdate();
	void soundRelease();
	void systemClose();
	void systemRelease();

};

#endif // !PLAYER_H