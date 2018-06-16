#ifndef PLAYER_H
#define PLAYER_H

#include "Song.h"
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
	FMOD::System	*system_; //system obj: will play sound
	FMOD::Sound		*sound_; //sounds we play: initial reference to sound & actual sound we play (potentially useful for referencing
	FMOD::Channel	*channel_ = 0; //channel we are going to play in
	FMOD_RESULT		result_; //error checking result for play operations
	unsigned int	version_; //version of fmod being used
	void			*extraDriverData_ = 0; //extra driver data that is initialised - good practice to get this (helps to play directly, I assume)

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