#include "playerIOHandler.h"

PlayerIOHandler::PlayerIOHandler()
{
}


PlayerIOHandler::~PlayerIOHandler()
{
}

IOHandler::KeyCode PlayerIOHandler::processInput()
{
	keyboardKeyCode = _getwch();
	return IOHandler::lookupKeyCode(keyboardKeyCode);
}

bool PlayerIOHandler::isPauseKey()
{
	return keyboardKeyCode == F3;
}

bool PlayerIOHandler::isExitKey()
{
	return keyboardKeyCode == ESC;
}

bool PlayerIOHandler::isVolumeUpKey()
{
	return keyboardKeyCode == W;
}

bool PlayerIOHandler::isVolumeDownKey()
{
	return keyboardKeyCode == S;
}

bool PlayerIOHandler::isSkipForwardKey()
{
	return keyboardKeyCode == F4;
}

bool PlayerIOHandler::isSkipBackKey()
{
	return keyboardKeyCode == F2;
}
