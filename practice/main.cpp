#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <algorithm>

#include <fstream>

#include "songregator.h"
#include "player.h"

using std::wcout; //use "wide" cout and cin to allow for UTF-8 characters
using std::wcin;
using std::flush;
using std::endl;

/*
	TODO list:
		* xxxx configure player to release/exit loop once song has finished (probably checking times or something)
		* modify vector<Song> in createSongList to be a map<wstring, vector<Song>> so artists exist
		* modify vector<Song> in createSongList so it's a map<wstring, map<vector<Song>>> so albums are a thing (or create a data structure for this nesting madness)
		* build thing to serialise/deserialise data. (SAVE/LOAD functionality)
		
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

	wstring baseDir = L"D:/Users/Jorta/Music/Saint Snow";
	bool filesFound = false;
	map<wstring, Artist> songregation = map<wstring, Artist>();

	Songregator songregator;
	while (!filesFound)
	{
		//wcout << L"Please enter your music directory: " << flush;
		//std::getline(std::wcin, baseDir);
		filesFound = songregator.createSongList(baseDir, songregation);
		if (!filesFound)
			wcout << L"Error creating song list. Please check the directory is correct and try again." << endl;
	}

	/*for (Song song : songregation)
	{
		wcout << "====================================================================" << endl;
		wcout << "Album: " << song.getAlbum() << endl;
		wcout << "Track No: " << song.getTrackNumber() << endl;
		wcout << "Title: " << song.getTitle() << endl;
		wcout << "Artist: " << song.getArtist() << endl;
		wcout << "====================================================================" << endl;
	}
	wcout << endl << endl;*/

	//Player player;
	//player.play(songregation.at(2).getFilePath().u8FilePath_);
	//player.play(songregation.at(6).getFilePath().u8FilePath_);

	Artist saintSnow = songregation.at(L"Saint Snow");
	vector<Song> awakenThePower = saintSnow.getAlbum(L"Awaken the power");

	Player player;
	player.play(awakenThePower.at(0).getFilePath().u8FilePath_);


	//program end
	wcout << "Press any key to continue.." << endl;
	wcin.clear();
	wcin.get();

	return 0;
}