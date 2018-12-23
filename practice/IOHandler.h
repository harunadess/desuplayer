#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <string>
#include <iostream>
#include <conio.h>

using std::string;
using std::wstring;
using std::wcout;
using std::wcin;
using std::endl;
using std::flush;
using std::end;

class IOHandler
{
public:
	IOHandler();
	~IOHandler();

	void outputTextInline(const wchar_t* output);
	void outputTextInline(const wstring& output);
	void outputNewline();
	void outputText(const wchar_t* output);
	void outputText(const wstring& output);
	void outputTextWithSpacing(const wchar_t* output);
	void outputTextWithSpacing(const wstring& output);
	void outputHeading(const wchar_t* output);
	void outputHeading(const wstring& output);
	
protected:
	enum KeyCode
	{
		UNMATCHED = -1,
		ESC = 27,
		SPC = 32,
		A = 97,
		D = 100,
		E = 101,
		L = 108,
		P = 112,
		Q = 113,
		R = 114,
		S = 115,
		W = 119,
		ARROW_INIT = 224,
		ARROW_UP = 72,
		ARROW_LEFT = 75,
		ARROW_RIGHT = 77,
		ARROW_DOWN = 80
	};
	int keyboardKeyCode_ = KeyCode::UNMATCHED;

	IOHandler::KeyCode lookupKeyCode(int keyCode);

private:
	const wchar_t* headingLine_ = L"========================================================";
};

#endif // !IO_HANDLER_H
