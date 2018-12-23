#include "playerIOHandler.h"

PlayerIOHandler::PlayerIOHandler()
{
}


PlayerIOHandler::~PlayerIOHandler()
{
}

IOHandler::KeyCode PlayerIOHandler::processInput()
{
	this->keyboardKeyCode_ = _getwch();
	return IOHandler::lookupKeyCode(this->keyboardKeyCode_);
}

bool PlayerIOHandler::isPauseKey()
{
	return (this->keyboardKeyCode_ == IOHandler::KeyCode::SPC);
}

bool PlayerIOHandler::isExitKey()
{
	return (this->keyboardKeyCode_ == IOHandler::KeyCode::ESC);
}
