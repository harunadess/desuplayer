#include "controller.h"

using std::wstring;
using std::vector;
using std::map;
using std::wcin;
using std::wcout;
using std::endl;
using std::flush;
using std::getline;

Controller::Controller()
{
}

Controller::~Controller()
{
}

//This should find out if the library file exists
// Use FileSystem to check if the file exists
// If it does, load it, call main
// If it does not exist,
// Do the initialisation code (Songregator)

// Note: MusicLibrary should contain a Songregator, directory path and stuff.
int Controller::init()
{
	bool libLoadSucc = m_fileSystem.loadMusicLibrary(m_musicLibrary);
	if (libLoadSucc)
	{
		m_io.outputText(L"Successfully loaded library!");
		return main();
	}
	else
	{
		m_io.outputText(L"Unable to find library file. Perform first time setup?\n1. Yes\n2. No (exit)");
		wstring response = L"";
		int nResponse = -1;
		bool validResponse = false;

		while (!validResponse)
		{
			m_io.outputTextInline(L">> ");
			getline(wcin, response);

			try
			{
				nResponse = std::stoi(response);
				validResponse = true;
			}
			catch (std::exception e)
			{
				m_io.outputText(L"Invalid response received.");
				nResponse = -1;
			}
		}

		if (nResponse == 1)
		{
			m_io.outputTextWithSpacing(L"Performing first time setup...");
			bool setupSucc = firstTimeSetup();
			if (setupSucc)
			{
				m_io.outputTextWithSpacing(L"Setup success!");
				return main();
			}
			else
			{
				m_io.outputTextWithSpacing(L"Setup failed...");
				return 1;
				//print error, retry.
			}
		}
		else
		{
			exit(0);
		}
	}
}

//todo: how do you populate/add things/view playlists??
const wstring getMainMenuText()
{
	wstring s = L"\n\n";
	s += L"Type \"play\" followed by search terms to play any song, artist, album or playlist.\n";
	s += L"Type \"search\" followed by search terms to find and print results.\n";
	s += L"Type \"queue\" followed by search terms to add the item to add the song/artist/album/playlist to the queue.\n";
	s += L"Type \"print\" to show what is currently in the queue.\n";
	s += L"Type \"start\" to play what is in the queue.\n";
	s += L"Type \"help\" to print this text.\n";
	s += L"Type \"exit\" to exit the application.\n";

	return s;
}

int Controller::main()
{
	m_io.outputHeading(L"        Console Music Player        ");
	
	wstring response = L"";
	wstring output = L"";

	m_io.outputText(getMainMenuText());
	while (true)
	{
		try
		{
			m_io.outputTextInline(L">> ");
			getline(wcin, response);

			handleResponse(response);
		}
		catch (std::exception e)
		{
			std::wcerr << L"Some kinda error in main input loop: " << e.what() << endl;
		}
	}

	return 0;
}

void Controller::handleResponse(const wstring& response) //todo: convert handle<x>Outcome functions to use m_io 
{
	vector<wstring> parsedResponse = parseResponse(response);
	InputOutcome outcome = checkResponse(parsedResponse[0]);
	
	size_t parsedResponseLen = parsedResponse[0].length();

	wstring searchTerms = response;
	if (outcome == InputOutcome::PLAY || outcome == InputOutcome::SEARCH || outcome == InputOutcome::QUEUE)
		searchTerms = searchTerms.replace(searchTerms.begin(), (searchTerms.begin() + parsedResponseLen + 1), L"");
	
	SearchResults searchResults;

	if(outcome == PLAY)
		handlePlayOutcome(searchTerms, searchResults);
	else if (outcome == SEARCH)
		handleSearchOutcome(searchTerms, searchResults);
	else if (outcome == QUEUE)
		handleQueueOutcome(searchTerms, searchResults);
	else if (outcome == PRINT)
		handlePrintOutcome();
	else if (outcome == START)
		handleStartOutcome();
	else if (outcome == HELP)
		handleHelpOutcome(searchTerms, searchResults);
	else if (outcome == EXIT)
		handleExitOutcome(searchTerms, searchResults);
	else 
		m_io.outputText(L"Unrecognised action. Use 'help' command for usage info.");
}

vector<wstring> Controller::parseResponse(const wstring& response) const
{
	vector<wstring> inputWords = vector<wstring>();
	wstring word = L"";
	wchar_t c = L'.';
	for (int i = 0; i < response.length(); i++)
	{
		c = response.at(i);
		if (c == L' ')
		{
			inputWords.push_back(word);
			word = L"";
		}
		else
		{
			word.push_back(c);
		}
	}

	if (word != L"")
		inputWords.push_back(word);

	return inputWords;
}

Controller::InputOutcome Controller::checkResponse(const wstring& response) const
{
	if (response == POSSIBLE_ACTIONS[0])
		return PLAY;
	else if (response == POSSIBLE_ACTIONS[1])
		return SEARCH;
	else if (response == POSSIBLE_ACTIONS[2])
		return QUEUE;
	else if (response == POSSIBLE_ACTIONS[3])
		return PRINT;
	else if (response == POSSIBLE_ACTIONS[4])
		return START;
	else if (response == POSSIBLE_ACTIONS[5])
		return HELP;
	else if (response == POSSIBLE_ACTIONS[6])
		return EXIT;
	else
		return UNRECOGNISED;
}

void Controller::handlePlayOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	bool succ = fullSearch(searchTerms, searchResults);
	if (!succ)
	{
		m_io.outputTextWithSpacing(L"Error in library search");
		return;
	}
	
	int maxOption = printSearchResults(searchResults);
	wstring chosen = L"";

	size_t nChosen = -1;
	m_io.outputTextInline(L"Enter a number from the search results, or -1 to exit.\n>> ");

	while (nChosen <= 0 || nChosen > maxOption)
	{
		try
		{
			getline(wcin, chosen);
			nChosen = std::stoi(chosen);

			if (nChosen == -1)
				return;
		}
		catch (std::exception e)
		{
			std::wcout << L"Invalid option received: " << e.what() << endl;
			nChosen = -1;
		}
	}

	if (searchResults.artists.size() > 0 && nChosen <= searchResults.artists.size())
		m_mediaPlayer.addToAdHocQueue(searchResults.artists.at(--nChosen));
	
	nChosen -= searchResults.artists.size();

	if (searchResults.albums.size() > 0 && nChosen <= searchResults.albums.size())
		m_mediaPlayer.addToAdHocQueue(searchResults.albums.at(--nChosen));
	
	nChosen -= searchResults.albums.size();

	if (searchResults.songs.size() > 0 && nChosen <= searchResults.songs.size())
		m_mediaPlayer.addToAdHocQueue(searchResults.songs.at(--nChosen));

	m_mediaPlayer.playImmediate();
}

void Controller::handleSearchOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	bool succ = fullSearch(searchTerms, searchResults);
	if (!succ)
	{
		m_io.outputTextWithSpacing(L"Error in library search");
		return;
	}

	printSearchResults(searchResults);
}

void Controller::handleQueueOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	bool succ = fullSearch(searchTerms, searchResults);
	if (!succ)
	{
		m_io.outputTextWithSpacing(L"Error in library search");
		return;
	}

	int maxOption = printSearchResults(searchResults);
	wstring chosen = L"";

	size_t nChosen = -1;
	m_io.outputTextInline(L"Enter a number from the search results, or -1 to exit.\n>> ");

	while (nChosen <= 0 || nChosen > maxOption)
	{
		try
		{
			getline(wcin, chosen);
			nChosen = std::stoi(chosen);

			if (nChosen == -1)
				return;
		}
		catch (std::exception e)
		{
			std::wcerr << L"Invalid option received: " << e.what() << endl;
			nChosen = -1;
		}
	}

	if (searchResults.artists.size() > 0 && nChosen <= searchResults.artists.size())
		m_mediaPlayer.addToPlaybackQueue(searchResults.artists.at(--nChosen));
	
	nChosen -= searchResults.artists.size();

	if (searchResults.albums.size() > 0 && nChosen <= searchResults.albums.size())
		m_mediaPlayer.addToPlaybackQueue(searchResults.albums.at(--nChosen));
	
	nChosen -= searchResults.albums.size();

	if (searchResults.songs.size() > 0 && nChosen <= searchResults.songs.size())
		m_mediaPlayer.addToPlaybackQueue(searchResults.songs.at(--nChosen));

	m_io.outputText(L"Successfully queued item(s)");
}

void Controller::handlePrintOutcome()
{
	vector<Song> songList = m_mediaPlayer.getPlaybackQueue()->getSongList();

	m_io.outputNewline();
	m_io.outputHeading(L"   Queue   ");
	int index = 1;
	for (Song s : songList)
	{
		wcout << index++ << L". " << flush;
		m_io.outputText(s.getTitle() + L"(" + s.getAlbumTitle() + L") - " + s.getArtistName());
	}

	m_io.outputNewline();
}

void Controller::handleStartOutcome()
{
	m_io.outputText(L"Playing queued items...");
	m_mediaPlayer.playQueued();
}

void Controller::handleHelpOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	m_io.outputText(getMainMenuText());
}

void Controller::handleExitOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	wcout << flush;
	exit(0);
}

bool Controller::fullSearch(const wstring& searchTerms, SearchResults& searchResults) const
{
	return m_musicLibrary.fullSearch(searchTerms, searchResults);
}

int Controller::printSearchResults(SearchResults& searchResults)
{
	int maxOption = 0;
	m_io.outputTextWithSpacing(L"Artists Found: ");
	for (Artist a : searchResults.artists)
	{
		wcout << ++maxOption << L". " << flush;  //todo: change m_io to use auto? or something..
		m_io.outputText(a.getName());
	}

	if (searchResults.artists.size() <= 0)
		m_io.outputText(L"<---  No results  --->");

	m_io.outputTextWithSpacing(L"Albums Found: ");
	for (Album a : searchResults.albums)
	{
		wcout << ++maxOption << L". " << flush;
		m_io.outputText((a.getTitle() + L" - " + a.getArtistName()));
	}

	if (searchResults.albums.size() <= 0)
		m_io.outputText(L"<---  No results  --->");
	
	m_io.outputTextWithSpacing(L"Songs Found: ");
	for (Song s : searchResults.songs)
	{
		wcout << ++maxOption << L". " << flush;
		m_io.outputText((s.getTitle() + L"(" + s.getAlbumTitle() + L") - " + s.getArtistName()));
	}

	if (searchResults.songs.size() <= 0)
		m_io.outputText(L"<---  No results  --->");

	m_io.outputNewline();

	return maxOption;
}

bool Controller::firstTimeSetup()
{
	wstring baseDir = L"";
	bool filesFound = false;
	m_io.outputText(L"Enter your root music folder (e.g. C:/Users/<user>/Music/)");
	while (!filesFound)
	{
		m_io.outputTextInline(L">> ");
		std::getline(std::wcin, baseDir);
		m_io.outputTextWithSpacing(L"Checking directory...");

		filesFound = m_musicLibrary.populate(baseDir);

		if (!filesFound)
			m_io.outputText(L"No items found in directory. Please check the directory path is correct.");
	}

	return m_fileSystem.saveMusicLibrary(m_musicLibrary);
}
