#ifndef PLAYER_H
#define PLAYER_H

#include "Song.h"
#include "Third Party/lowlevel/inc/fmod.hpp"
#include "Third Party/lowlevel/inc/fmod_common.h"

class Player
{
public:
	Player();
	~Player();

	void play(Song* song);
	bool isPlaying(bool playing);
	bool isPaused(bool paused);
	void getPosition(unsigned int ms);

private:
	FMOD::System	*system; //system obj: will play sound
	FMOD::Sound		*sound; //sounds we play: initial reference to sound & actual sound we play (potentially useful for referencing
	FMOD::Channel	*channel = 0; //channel we are going to play in
	FMOD_RESULT		result; //error checking result for play operations
	unsigned int	version; //version of fmod being used
	void			*extraDriverData = 0; //extra driver data that is initialised - good practice to get this (helps to play directly, I assume)

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