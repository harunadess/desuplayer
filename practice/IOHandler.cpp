#include "ioHandler.h"

using std::wstring;
using std::wcout;
using std::endl;
using std::flush;

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
	wcout << m_HEADING_LINE << endl 
		<< "  " << output << endl 
		<< m_HEADING_LINE << endl;
}

void IOHandler::outputHeading(const wstring& output)
{
	wcout << m_HEADING_LINE << endl
		<< "  " << output << endl
		<< m_HEADING_LINE << endl;
}

IOHandler::KeyCode IOHandler::lookupKeyCode(int keyCode)
{
	if (keyCode == FUNCTION_INIT)
	{
		keyCode = _getwch();
		if (keyCode == F2)
			return F2;
		else if (keyCode == F3)
			return F3;
		else if (keyCode == F4)
			return F4;
	}
	else 
	{
		if (keyCode == ESC)
			return ESC;
		else if (keyCode == SPC)
			return SPC;
		else if (keyCode == A)
			return A;
		else if (keyCode == D)
			return D;
		else if (keyCode == E)
			return E;
		else if (keyCode == L)
			return L;
		else if (keyCode == P)
			return P;
		else if (keyCode == Q)
			return Q;
		else if (keyCode == R)
			return R;
		else if (keyCode == S)
			return S;
		else if (keyCode == W)
			return W;
		else
			return UNMATCHED;
	}
}
