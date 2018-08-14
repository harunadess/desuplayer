﻿#include <iostream>
#include <Windows.h>
#include <string>
#include <fcntl.h>
#include <io.h>

#include <fstream>

#include "Player.h"
#include "IOHandler.h"
#include "PlayerIOHandlerr.h"
#include "FileSystem.h"

using std::wcout; //use "wide" cout and cin to allow for UTF-8 characters
using std::wcin;
using std::flush;
using std::endl;

/*
	ToDo list:
		* xxxx Comment more on parts of the Play function to understand what all the bits are doing.
		* xxxx Split out functions into managable functions that make sense (in same file).
		* xxxx Split out main loop into core play function. (could do more to fix this)
		* xxxx Make new fangled io handler
		* xx Modify current io to use new fangled io handler
			* Split current IOHandler into one for text input and another for keyboard keycodes
		
		* xxxx Research ways of scanning directories for files
		* xx Display UTF-8 encoded characters in the console
			* Find better font
		* save ^ data somehow (.txt, .bin, .ini, ..probably not .json (no idea how to work with json in cpp)
		* 
*/

//void start(int argc)
//{
//	program start
//	wcout << "========================================================================" << endl;
//	wcout << "\t\t\tProgram Start" << endl;
//	wcout << "========================================================================" << endl;
//
//	//Song* song = new Song("Determination Symphony", new Album("Determination Symphony"), new Artist("Roselia"));
//	string title = "Determination Symphony";
//	Artist* artist = new Artist("Roselia");
//	Album* album = new Album(title, artist);
//
//	Song* song = new Song(title, album, artist);
//	song->setFilePath("../media/sound.mp3");
//
//	Player* musicPlayer = new Player();
//	musicPlayer->play(song);
//
//	delete musicPlayer;
//	delete song;
//}

//void test_io(int argc)
//{
//	const char* message1 = "test message";
//	const char* message2 = "another test message";
//
//	IOHandler* io = new IOHandler();
//	io->outputHeading("whoa, this is a great heading!!");
//
//	io->outputTextInline(message1);
//	io->outputTextInline(" and a little bit extra");
//	
//	io->outputNewline();
//	io->outputText(message1);
//	io->outputText(message2);
//
//	io->outputTextWithSpacing(message1);
//	io->outputTextWithSpacing(message2);
//
//	//clean up
//	delete io;
//}

//void test_keypress(int argc)
//{
//	PlayerIOHandlerr* io = new PlayerIOHandlerr();
//	io->test_keypress();
//}

void test_fileSystem(int argc)
{
	FileSystem* fileSystem = new FileSystem();
	wchar_t* baseDir = new wchar_t(L'/');
	
	bool validDir = false;
	while (!validDir)
	{
		wcout << L"Please enter your base music directory:" << flush;
		wcin >> baseDir;

		validDir = fileSystem->scanForNewFiles(baseDir);
		if (!validDir)
			wcout << L"Could not find or access directory. Please check the location and try again." << endl;
	}
}

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

void test_ioFile(int argc)
{
	class Data {
	public:
		const wchar_t* key;
		const wchar_t* value;
	};
	Data *x = new Data();
	x->key = L"some text";
	x->value = L"こんにちは、友達";

	wcout << "x->key = " << x->key << endl;
	wcout << "x->key = " << x->value << endl;

	std::fstream file("_file.bin", std::fstream::out | std::fstream::binary);
	file.seekp(0);
	file.write((char*)x, sizeof(Data));
	file.close();

	file.open("_file.bin", std::fstream::in | std::fstream::binary);

	Data* y = new Data();

	file.seekp(0);
	file.read((char*)y, sizeof(Data));
	file.close();

	wcout << "y->key = " << y->key << endl;
	wcout << "y->key = " << y->value << endl;
}

int wmain(int argc, wchar_t* argv[])
{
	configConsole();
	//start(argc); //hand off to start function for music player
	//test_io(argc); //testing io handler
	//test_keypress(argc); //testing keypress stuff
	//test_fileSystem(argc); //testing file stuff

	test_ioFile(argc);

	//program end
	wcout << "Press any key to continue.." << endl;
	wcin.clear();
	wcin.get();

	return 0;
}