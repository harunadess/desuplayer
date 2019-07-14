#ifndef PLAYERIOHANDLER_H
#define PLAYERIOHANDLER_H

#include "IOHandler.h"

class PlayerIOHandler 
	: public IOHandler
{
public:
	PlayerIOHandler();
	~PlayerIOHandler();

	IOHandler::KeyCode processInput();
	bool isPauseKey();
	bool isExitKey();
	bool isVolumeUpKey();
	bool isVolumeDownKey();
	bool isSkipForwardKey();
	bool isSkipBackKey();

};

#endif // !PLAYERIOHANDLER_H
