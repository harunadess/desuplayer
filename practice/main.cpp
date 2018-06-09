#include <iostream>
#include <string>
#include "Player.h"

using std::cout;
using std::cin;
using std::flush;
using std::endl;

/*
	ToDo list:
		* Comment more on parts of the Play function to understand what all the bits are doing.
		* Split out functions into managable functions that make sense (in same file).
		* Split out main loop into core play function.
		
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

	Song* song = new Song("Determination Symphony", new Album("Determination Symphony"), new Artist("Roselia"));
	song->setFilePath("../media/sound.mp3");

	Player* musicPlayer = new Player();
	musicPlayer->play(song);

	delete musicPlayer;
	delete song;
}

int main(int argc)
{
	start(argc); //hand off to start function

	//program end
	cout << "Program exit" << endl;
	cin.clear();
	cin.get();

	return 0;
}