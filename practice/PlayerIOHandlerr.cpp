#include "PlayerIOHandlerr.h"

PlayerIOHandlerr::PlayerIOHandlerr()
{
}


PlayerIOHandlerr::~PlayerIOHandlerr()
{
}

IOHandler::KeyCode PlayerIOHandlerr::processInput()
{
	keyboardKeyCode_ = _getwch();
	return IOHandler::lookupKeyCode(keyboardKeyCode_);
}
