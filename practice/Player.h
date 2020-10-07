#ifndef PLAYER_H
#define PLAYER_H

#include "ThirdParty/lowlevel/inc/fmod.hpp"
#include "ThirdParty/lowlevel/inc/fmod_errors.h"
#include "ThirdParty/lowlevel/inc/fmod_common.h"

#include "playerIOHandler.h"
#include "mpControls.h"
#include "ipc.h"
#include "playDeets.h"

class Player
{
public:
	Player(MpControls& mpControls, IPC* ipc);
	~Player();

	//int play(std::string filePath);
	void play(PlayDeets& playDeets);
	void checkIsPlaying(bool& playing);
	void checkIsPaused(bool& paused);
	void getSeekPosition(unsigned int& ms);
	void getLength(unsigned int& ms);
	int getVolume();
	void setVolume(const int& volume);

	enum ExitCode {
		NORMAL,
		EXIT,
		NEXT,
		PREVIOUS,
		STOP
	};

protected:
	IPC* m_ipc;

private:
	void initialize();
	void systemCreate();
	void getFmodVersion();
	void checkFmodVersion();
	void systemInitialize();
	void createStream(const char* songLocation);
	void playSound();
	int corePlayLoop();
	void checkForInput(int& exitCode);
	void systemUpdate();
	void getVolumeInternal(float& volume);
	void setVolumeInternal(float& volume);
	void soundRelease();
	void systemClose();
	void systemRelease();

	void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);

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
	PlayerIOHandler* m_io;


	float* m_currentVolume = nullptr;

	const float MAX_VOLUME = 1.0f;
	const float MIN_VOLUME = 0.0f;
	const float DEFAULT_VOLUME = 0.5f;

	MpControls* m_mpControls;
};

#endif // !PLAYER_H
