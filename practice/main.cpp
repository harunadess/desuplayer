#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <algorithm>

#include "songregator.h"
#include "controller.h"

using std::wcout; //use "wide" cout and cin to allow for UTF-8 characters
using std::wcin;
using std::flush;
using std::endl;

using std::wstring;

/*
	TODO list:
	* Need a display interface
		* Display things in library
			* Artists
				* Albums
				* Songs
			* Playlists
		* Way to add things to play
	
	* Need a control interface
		* Way to control player in a more reasonable manner
			* Media keys???

	* If you're planning on having a non-blocking console, what you need is:
			* One thread for the menu
			* One for the player/a console output

	* Need a better way to handle errors, as currently I don't really do that
		# void bois out in fashion

	* Find better font (LOOKS)
*/

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

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFontInfo);
}

void miscTest()
{
	while (!_kbhit())
	{
	}
	wprintf(L"\nKey struck was '%d'\n", _getch());
}


//todo: need to fix initial program startup
// -> get and fill library

//todo: need to fix non-initial program startup
// - > library scan to update library

//todo: general program workings
// -> need to ensure that *ALL* output is wide. Otherwise it'll throw errors and stuff I think [ALL]

// -> can you fix the text of the controls appearing? [player.cpp] -> move text to [controller.cpp/musicplayer.cpp]

int wmain(int argc, wchar_t* argv[])
{
	configConsole();
	
	Controller* controller = new Controller();
	int exitCode = controller->init();

	delete controller;

	return exitCode;
}
