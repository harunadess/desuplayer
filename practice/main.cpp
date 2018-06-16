#include <iostream>
#include <string>
#include "Player.h"
#include "IOHandler.h"

using std::cout;
using std::cin;
using std::flush;
using std::endl;

/*
	ToDo list:
		* xxxx Comment more on parts of the Play function to understand what all the bits are doing.
		* xxxx Split out functions into managable functions that make sense (in same file).
		* xx Split out main loop into core play function. (could do more to fix this
		* Modify current io to use new fangled io handler
		
		* Research ways of scanning directories for files
		* save ^ data somehow
		* 
*/

void start(int argc)
{
	//program start
	cout << "========================================================================" << endl;
	cout << "\t\t\tProgram Start" << endl;
	cout << "========================================================================" << endl;

	/*Song* song = new Song("Determination Symphony", new Album("Determination Symphony"), new Artist("Roselia"));*/
	string title = "Determination Symphony";
	Artist* artist = new Artist("Roselia");
	Album* album = new Album(title, artist);

	Song* song = new Song(title, album, artist);
	song->setFilePath("../media/sound.mp3");

	Player* musicPlayer = new Player();
	musicPlayer->play(song);

	delete musicPlayer;
	delete song;
}

void test_io(int argc)
{
	const char* message1 = "test message";
	const char* message2 = "another test message";

	IOHandler* io = new IOHandler();
	io->outputHeading("whoa, this is a great heading!!");

	io->outputTextInline(message1);
	io->outputTextInline(" and a little bit extra");
	
	io->outputNewline();
	io->outputText(message1);
	io->outputText(message2);

	io->outputTextWithSpacing(message1);
	io->outputTextWithSpacing(message2);

	//clean up
	delete io;
}

void test_keypress(int argc)
{
	IOHandler* io = new IOHandler();
	io->test_keypress();
}

int main(int argc)
{
	//start(argc); //hand off to start function for music player
	//test_io(argc); //testing io handler
	test_keypress(argc); //testing keypress stuff
	//program end
	cout << "Press any key to continue.." << endl;
	cin.clear();
	cin.get();


	return 0;
}