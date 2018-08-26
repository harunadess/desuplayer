#include "playerIOHandler.h"

PlayerIOHandlerr::PlayerIOHandlerr()
{
}


PlayerIOHandlerr::~PlayerIOHandlerr()
{
}

IOHandler::KeyCode PlayerIOHandlerr::processInput()
{
	this->keyboardKeyCode_ = _getwch();
	return IOHandler::lookupKeyCode(this->keyboardKeyCode_);
}

bool PlayerIOHandlerr::isPauseKey()
{
	return (this->keyboardKeyCode_ == IOHandler::KeyCode::SPC);
}

bool PlayerIOHandlerr::isExitKey()
{
	return (this->keyboardKeyCode_ == IOHandler::KeyCode::ESC);
}
