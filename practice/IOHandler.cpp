#include "IOHandler.h"


IOHandler::IOHandler()
{
}


IOHandler::~IOHandler()
{
}

void IOHandler::outputTextInline(const char* output)
{
	cout << output << " " << flush;
}

void IOHandler::outputNewline()
{
	cout << "\n" << flush;
}

void IOHandler::outputText(const char* output)
{
	cout << output << endl;
}

void IOHandler::outputTextWithSpacing(const char* output)
{
	cout << endl << output << endl;
}

void IOHandler::outputHeading(const char* output)
{
	cout << headingLine_ << endl 
		<< "  " << output << endl 
		<< headingLine_ << endl;
}

string IOHandler::lookupKeyCode(int keyCode)
{
	switch (keyCode)
	{
	case KeyCode::ESC:
		return "Escape";
	case KeyCode::SPC:
		return "Spacebar";
	case KeyCode::A:
		return "A";
	case KeyCode::D:
		return "D";
	case KeyCode::E:
		return "E";
	case KeyCode::L:
		return "L";
	case KeyCode::P:
		return "P";
	case KeyCode::Q:
		return "Q";
	case KeyCode::R:
		return "R";
	case KeyCode::S:
		return "S";
	case KeyCode::W:
		return "W";
	//Arrow key initially returns this keycode
	case KeyCode::ARROW_INIT:
		return "";
	//Arrow key returns actual keycode after initial
	case KeyCode::ARROW_UP:
		return "Arrow Up";
	case KeyCode::ARROW_LEFT:
		return "Arrow Left";
	case KeyCode::ARROW_RIGHT:
		return "Arrow Right";
	case KeyCode::ARROW_DOWN:
		return "Arrow Down";
	default:
		return "";
	}
}

void IOHandler::test_keypress()
{
	cout << "Press a key." << endl;
	
	int keyValue = 0;
	string keyPressed;
	while (true)
	{
		keyPressed = "/";
		keyValue = _getwch();
		keyPressed = lookupKeyCode(keyValue);
		if (keyPressed != "")
		{
			cout << keyPressed << endl;
		}
	}
}