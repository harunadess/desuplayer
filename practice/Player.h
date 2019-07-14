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

	int play(std::string filePath);
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
	int corePlayLoop();
	void systemUpdate();
	void getVolume(float& volume);
	void setVolume(float& volume);
	void soundRelease();
	void systemClose();
	void systemRelease();

	//system obj: will play sound
	FMOD::System* m_system;
	//actual audio
	FMOD::Sound* m_sound;
	//current audio channel
	FMOD::Channel* m_channel = nullptr;
	//error checking result for most actions taken by FMOD
	FMOD_RESULT m_result;
	//version of fmod being used
	unsigned int m_version;
	//extra driver data of audio subsystem
	void* m_extraDriverData = nullptr;
	PlayerIOHandler *m_io;

	const float MAX_VOLUME = 1.0f;
	const float MIN_VOLUME = 0.0f;
	const float VOLUME_INCREMENT = 0.05f;
};

#endif // !PLAYER_H
