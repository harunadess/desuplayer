#ifndef PLAYER_H
#define PLAYER_H

#include "Song.h"
#include "PlayerIOHandlerr.h"
#include "ThirdParty/lowlevel/inc/fmod.hpp"
#include "ThirdParty/lowlevel/inc/fmod_common.h"

class Player
{
public:
	Player();
	~Player();

	void play(Song* song);
	bool checkIsPlaying(bool& playing);
	bool checkIsPaused(bool& paused);
	unsigned int getSeekPosition(unsigned int ms);

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
	PlayerIOHandlerr *io_;

	void initialize();
	void systemCreate();
	void getFmodVersion();
	void checkFmodVersion();
	void systemInitialize();
	void createStream(const char *songLocation);
	void playSound();
	void corePlayLoop();
	void systemUpdate();
	void soundRelease();
	void systemClose();
	void systemRelease();

};

#endif // !PLAYER_H