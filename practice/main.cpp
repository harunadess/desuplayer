#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <algorithm>
#include <fstream>

#include "songregator.h"
#include "player.h"
#include "fileSystem.h"
#include "musicLibrary.h"

#include "frontend.h"

using std::wcout; //use "wide" cout and cin to allow for UTF-8 characters
using std::wcin;
using std::flush;
using std::endl;

/*
	TODO list:
	* Build actual console-appy part of application. Or, modify the main to run based off parameters (might be fun, could be added to cmd path and invoked anywhere)
	* Build wrapper for player (or polymorph some shit onto that (i.e. musicPlayer) which handles some of the manual shit for player (adding songs, having a queue and stuff)
	* xxxx use thing to serialise/deserialise data.
		* endless summer sub-task: add save/load archive method to each subclass depending on what there is in MusicLibrary
		
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

void start(int argc)
{
	//program start
	wcout << "========================================================================" << endl;
	wcout << "\t\t\tProgram Start" << endl;
	wcout << "========================================================================" << endl;
}


//Song test_fileSystem(int argc)
//{
//	wstring baseDir = L"D:\\Users\\Jorta\\Music";
//	FileFinder* fileFinder = new FileFinder();
//	vector<FilePath> foundFiles = fileFinder->scanForNewFiles(baseDir);
//	
//	//BIG WARNING: CANNOT USE/PLAY FILE IF TAGLIB IS USING IT.
//	//GET TAGS
//	//DESTRUCT FILEREFS
//	//THEN FREE TO PLAY FILES
//
//	TagLib::FileRef f(foundFiles.at(266).wideFilePath_.c_str());
//	
//	wstring t = f.tag()->title().toWString();
//	wstring al = f.tag()->album().toWString();
//	wstring ar = f.tag()->artist().toWString();
//
//	///////////////////////////////////////////////
//	//todo: rewrite when song constructor finished.
//	///////////////////////////////////////////////
//	//Song s(t, new Album(al, new Artist(ar)), new FilePath(foundFiles.at(266)));
//
//	//return s;
//	return Song();
//}

//void test_ioFile(int argc)
//{
//	class Data {
//	public:
//		const wchar_t* key;
//		const wchar_t* value;
//	};
//	Data *x = new Data();
//	x->key = L"some text";
//	x->value = L"こんにちは、友達";
//
//	wcout << "x->key = " << x->key << endl;
//	wcout << "x->key = " << x->value << endl;
//
//	std::fstream file("_file.bin", std::fstream::out | std::fstream::binary);
//	file.seekp(0);
//	file.write((char*)x, sizeof(Data));
//	file.close();
//
//	file.open("_file.bin", std::fstream::in | std::fstream::binary);
//
//	Data* y = new Data();
//
//	file.seekp(0);
//	file.read((char*)y, sizeof(Data));
//	file.close();
//
//	wcout << "y->key = " << y->key << endl;
//	wcout << "y->key = " << y->value << endl;
//}

int wmain(int argc, wchar_t* argv[])
{
	configConsole();
	//start(argc);							//hand off to start function for music player
	//test_io(argc);						//testing io handler
	//test_keypress(argc);					//testing keypress stuff
	//Song s = test_fileSystem(argc);				//testing file stuff
	//test_ioFile(argc);					//testing storing shit in files

	///This is new testing stuff
	{
		wstring baseDir = L"D:/Users/Jorta/Music/"; //todo: change separators for "\\" if "/" is used or the std::filesystem::some_special_separator_thing
		bool filesFound = false;
		MusicLibrary musicLibrary;

		Songregator songregator;
		while (!filesFound)
		{
			//wcout << L"Please enter your music directory: " << flush;
			//std::getline(std::wcin, baseDir);
			filesFound = songregator.createSongList(baseDir, musicLibrary);
			if (!filesFound)
				wcout << L"Error creating song list. Please check the directory is correct and try again." << endl;
		}

		///We have the data, time to do something with it
		//Artist roselia = musicLibrary.getArtist(L"Roselia");
		//vector<Song> anfang = roselia.getAlbum(L"Anfang");

	//	/*Player player;
	//	player.play(anfang.at(0).getFilePath().u8FilePath_);
	//	player.play(anfang.at(1).getFilePath().u8FilePath_);*/

		///testing saving
		FileSystem fs;
		fs.saveMusicLibrary(musicLibrary);
	}

	/////testing loading
	/*{
		MusicLibrary musicLibrary;

		FileSystem fs;
		fs.loadMusicLibrary(musicLibrary);

		wcout << L"loaded library" << endl;
		Artist roselia = musicLibrary.getArtist(L"Roselia");
		vector<Song> anfang = roselia.getAlbum(L"Anfang");

		Player player;
		player.play(anfang.at(0).getFilePath().u8FilePath_);
		player.play(anfang.at(1).getFilePath().u8FilePath_);
	}*/

	/*FrontEnd frontend;
	int frontendReturn = 0;
	frontendReturn =  frontend.main(argc, argv);*/

	//program end
	/*wcout << "Press any key to continue.." << endl;
	wcin.clear();
	wcin.get();*/

	return 0;
}
