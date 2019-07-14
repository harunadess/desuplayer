#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <string>
#include <iostream>
#include <conio.h>

//todo: could refactor this class to just use auto& to then print things.
class IOHandler
{
public:
	IOHandler();
	~IOHandler();

	void outputTextInline(const wchar_t* output);
	void outputTextInline(const std::wstring& output);
	void outputNewline();
	void outputText(const wchar_t* output);
	void outputText(const std::wstring& output);
	void outputTextWithSpacing(const wchar_t* output);
	void outputTextWithSpacing(const std::wstring& output);
	void outputHeading(const wchar_t* output);
	void outputHeading(const std::wstring& output);
	
protected:
	enum KeyCode
	{
		UNMATCHED = -1,
		FUNCTION_INIT = 0,
		F2 = 60,
		F3 = 61,
		F4 = 62,
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
		W = 119
	};

	IOHandler::KeyCode lookupKeyCode(int& keyboardKeyCode);

	int keyboardKeyCode = KeyCode::UNMATCHED;

private:
	const wchar_t* m_HEADING_LINE = L"========================================================";

};

#endif // !IO_HANDLER_H
