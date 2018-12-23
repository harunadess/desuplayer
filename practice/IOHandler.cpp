#include "ioHandler.h"


IOHandler::IOHandler()
{
}


IOHandler::~IOHandler()
{
}

void IOHandler::outputTextInline(const wchar_t* output)
{
	wcout << output << " " << flush;
}

void IOHandler::outputTextInline(const wstring& output)
{
	wcout << output << " " << flush;
}

void IOHandler::outputNewline()
{
	wcout << "\n" << flush;
}

void IOHandler::outputText(const wchar_t* output)
{
	wcout << output << endl;
}

void IOHandler::outputText(const wstring& output)
{
	wcout << output << endl;
}

void IOHandler::outputTextWithSpacing(const wchar_t* output)
{
	wcout << endl << output << endl;
}

void IOHandler::outputTextWithSpacing(const wstring& output)
{
	wcout << endl << output << endl;
}

void IOHandler::outputHeading(const wchar_t* output)
{
	wcout << headingLine_ << endl 
		<< "  " << output << endl 
		<< headingLine_ << endl;
}

void IOHandler::outputHeading(const wstring& output)
{
	wcout << headingLine_ << endl
		<< "  " << output << endl
		<< headingLine_ << endl;
}

IOHandler::KeyCode IOHandler::lookupKeyCode(int keyCode)
{
	switch (keyCode)
	{
	case KeyCode::ESC:
		return KeyCode::ESC;
	case KeyCode::SPC:
		return KeyCode::SPC;
	case KeyCode::A:
		return KeyCode::A;
	case KeyCode::D:
		return KeyCode::D;
	case KeyCode::E:
		return KeyCode::E;
	case KeyCode::L:
		return KeyCode::L;
	case KeyCode::P:
		return KeyCode::P;
	case KeyCode::Q:
		return KeyCode::Q;
	case KeyCode::R:
		return KeyCode::R;
	case KeyCode::S:
		return KeyCode::S;
	case KeyCode::W:
		return KeyCode::W;
	//Arrow key initially returns this keycode
	case KeyCode::ARROW_INIT:
		return KeyCode::ARROW_INIT;
	//Arrow key returns actual keycode after initial
	case KeyCode::ARROW_UP:
		return KeyCode::ARROW_UP;
	case KeyCode::ARROW_LEFT:
		return KeyCode::ARROW_LEFT;
	case KeyCode::ARROW_RIGHT:
		return KeyCode::ARROW_RIGHT;
	case KeyCode::ARROW_DOWN:
		return KeyCode::ARROW_DOWN;
	default:
		return KeyCode::UNMATCHED;
	}
}
