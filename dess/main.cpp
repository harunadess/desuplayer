#include <Windows.h>
#include <fcntl.h>
#include <locale.h>
#include <io.h>
#include <iostream>
#include <vector>

const int BUFFER_SIZE = 4096;

void configConsole()
{
	//Set CodePage of console so it will be UTF-8 encoded
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	_setmode(_fileno(stdout), _O_U8TEXT);

	CONSOLE_FONT_INFOEX consoleFontInfo;
	consoleFontInfo.cbSize = (sizeof consoleFontInfo);
	consoleFontInfo.nFont = 0;
	consoleFontInfo.dwFontSize.X = 8;
	consoleFontInfo.dwFontSize.Y = 14; //main font size control (pt)
	consoleFontInfo.FontFamily = FF_DONTCARE;
	consoleFontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(consoleFontInfo.FaceName, L"MS Gothic"); //set font type, ms gothic seems to support most unicode characters

	bool succ = SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFontInfo);
}

int wmain(int argc, wchar_t* argv[])
{
	configConsole();

	bool succ = false;
	DWORD dwRead;
	HANDLE hStdIn, hStdOut;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


	if (hStdOut == INVALID_HANDLE_VALUE || hStdIn == INVALID_HANDLE_VALUE)
	{
		wprintf(L"invalid handle value\n");
		return 1;
	}

	wchar_t chBuf[BUFFER_SIZE];
	wchar_t* msg;
	while (true)
	{
		succ = ReadFile(hStdIn, chBuf, BUFFER_SIZE, &dwRead, NULL);

		if (!succ)
			break;
		if (dwRead == 0)
			break;

		long fp = ftell(stdin);
		fp /= sizeof(wchar_t);

		int len = dwRead / sizeof(wchar_t);
		
		msg = new wchar_t[len];
		lstrcpynW(msg, &chBuf[fp], len);

		wprintf(msg);

		if (!succ)
			break;
	}

	return 0;
}
