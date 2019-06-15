#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <algorithm>
#include <fstream>

#include "songregator.h"
//#include "player.h"
#include "mediaPlayer.h"
#include "fileSystem.h"
#include "musicLibrary.h"

#include "frontend.h"

using std::wcout; //use "wide" cout and cin to allow for UTF-8 characters
using std::wcin;
using std::flush;
using std::endl;

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

	* Need a way to handle errors, as currently I don't really do that
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
	consoleFontInfo.dwFontSize.Y = 14; //font size
	consoleFontInfo.FontFamily = FF_DONTCARE;
	consoleFontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(consoleFontInfo.FaceName, L"MS Gothic"); //set font type

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFontInfo); //set font to params above
}

void testSongFindAndSave()
{
	wstring baseDir = L"D:/Jorta/Music/";
	bool filesFound = false;
	MusicLibrary musicLibrary;
	Songregator songregator;

	while (!filesFound)
	{
		wcout << L"Please enter your music directory: " << flush;
		std::getline(std::wcin, baseDir);
		filesFound = songregator.createSongList(baseDir, musicLibrary);
		if (!filesFound)
			wcout << L"Error creating song list. Please check the directory is correct." << endl;
	}

	FileSystem fs;
	fs.saveMusicLibrary(musicLibrary);
}

void testSongLoadAndPlay()
{
	FileSystem fs;
	MusicLibrary musicLibrary;
	
	bool loadSucc = fs.loadMusicLibrary(musicLibrary);
	if (!loadSucc)
	{
		wcout << L"Failed to load library." << endl;
		exit(3);
	}
	wcout << L"Successfully loaded library" << endl;

	Artist roselia = musicLibrary.getArtist(L"Roselia");
	Album anfang(L"Roselia", roselia.getAlbum(L"Anfang"));

	MediaPlayer player;
	player.playImmediately(anfang);
}

void testfn(int testCase)
{
	switch (testCase)
	{
	case 1:
		testSongFindAndSave();
		break;
	case 2:
		testSongLoadAndPlay();
		break;
	default:
		break;
	}
}

int wmain(int argc, wchar_t* argv[])
{
	configConsole();

	testfn(1);
	testfn(2);

	return 0;
}
