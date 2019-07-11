#ifndef PLAYER_H
#define PLAYER_H

#include "ThirdParty/lowlevel/inc/fmod.hpp"
#include "ThirdParty/lowlevel/inc/fmod_errors.h"
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

	//system obj: will play sound
	FMOD::System* m_system;
	//actual audio
	FMOD::Sound* m_sound;
	//current audio channel
	FMOD::Channel* m_channel = 0;
	//error checking result for most actions taken by FMOD
	FMOD_RESULT m_result;
	//version of fmod being used
	unsigned int m_version;
	//extra driver data of audio subsystem
	void* m_extraDriverData = 0;
	PlayerIOHandler *m_io;

};

#endif // !PLAYER_H
