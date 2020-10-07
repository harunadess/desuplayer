#include "controller.h"

using std::wstring;
using std::vector;
using std::map;
using std::wcin;
using std::wcout;
using std::endl;
using std::flush;
using std::getline;

Controller::Controller(MpControls& mpControls, IPC* ipc)
	:m_mediaPlayer(mpControls, ipc)
{
}

Controller::~Controller()
{
	m_fileSystem.saveMusicLibrary(m_musicLibrary);
}

int Controller::getMenuOp(wstring& responseStr)
{
	bool validResponse = false;
	int nResponse = -1;

	while (!validResponse)
	{
		m_io.outputTextInline(L">> ");
		getline(wcin, responseStr);

		try
		{
			nResponse = std::stoi(responseStr);
			validResponse = true;
		}
		catch (std::exception e)
		{
			m_io.outputText(L"Invalid option received.");
			m_io.outputTextInline(L">> ");
			
			nResponse = -1;
			validResponse = false;
		}
	}

	return nResponse;
}

int Controller::init()
{
	bool libLoadSucc = m_fileSystem.loadMusicLibrary(m_musicLibrary);
	if (libLoadSucc)
	{
		m_io.outputText(L"Successfully loaded library!");
		return 0;
	}
	else
	{
		m_io.outputText(L"Unable to find library file. Perform first time setup?\n1. Yes\n2. No (exit)");
		wstring response = L"";
		int nResponse = getMenuOp(response);

		if (nResponse == 1)
		{
			m_io.outputTextWithSpacing(L"Performing first time setup...");
			bool setupSucc = firstTimeSetup();
			if (setupSucc)
			{
				m_io.outputTextWithSpacing(L"Setup success!");
				return 0;
			}
			else
			{
				m_io.outputTextWithSpacing(L"Setup failed...\n");
				m_io.outputText(L"Retry?\n1. Yes\n2. No (exit)");
				
				nResponse = getMenuOp(response);

				if(nResponse == 1)
					return init();
				else
					return 2;
			}
		}
		else
		{
			return 2;
		}
	}
}

const wstring getMainMenuText()
{
	wstring s = L"\n\n";
	s += L"Type \"play\" followed by search terms to play any song, artist, album or playlist.\n";
	s += L"Type \"search\" followed by search terms to print all matching results.\n";
	s += L"Type \"queue\" followed by search terms to add the item to add the song/artist/album/playlist to the queue.\n";
	s += L"Type \"print\" to show what is currently in the queue.\n";
	s += L"Type \"start\" to play what is in the queue.\n";
	s += L"Type \"volume\" and a percentage between 0 and 100 to set the volume to that amount.\n";
	s += L"Type \"save\" followed by a title to save the current queue as a playlist.\n";
	s += L"Type \"init\" to reinitialise the library, and scan for files again.\n";
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

void Controller::handleResponse(const wstring& response)
{
	vector<wstring> parsedResponse = parseResponse(response);
	InputOutcome outcome = checkResponse(parsedResponse[0]);
	
	size_t parsedResponseLen = parsedResponse[0].length();

	wstring outcomeArgs = response;
	if (outcome == PLAY || outcome == SEARCH || outcome == QUEUE || outcome == SAVE || outcome == VOLUME)
	{
		if (parsedResponse.size() > 1)
		{
			outcomeArgs = outcomeArgs.replace(outcomeArgs.begin(), (outcomeArgs.begin() + parsedResponseLen + 1), L"");
		}
		else
		{
			m_io.outputText(L"Please add arguments dess.");
			return;
		}
	}
	
	SearchResults searchResults;

	if (outcome == PLAY)
		handlePlayOutcome(outcomeArgs, searchResults);
	else if (outcome == SEARCH)
		handleSearchOutcome(outcomeArgs, searchResults);
	else if (outcome == QUEUE)
		handleQueueOutcome(outcomeArgs, searchResults);
	else if (outcome == PRINT)
		handlePrintOutcome();
	else if (outcome == START)
		handleStartOutcome();
	else if (outcome == VOLUME)
		handleVolumeOutcome(outcomeArgs);
	else if (outcome == SAVE)
		handleSaveOutcome(outcomeArgs);
	else if (outcome == INITIALISE)
		handleInitialiseOutcome();
	else if (outcome == HELP)
		handleHelpOutcome();
	else if (outcome == EXIT)
		handleExitOutcome();
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
	/*if (response == POSSIBLE_ACTIONS[PLAY])
		return PLAY;
	else if (response == POSSIBLE_ACTIONS[SEARCH])
		return SEARCH;
	else if (response == POSSIBLE_ACTIONS[QUEUE])
		return QUEUE;
	else if (response == POSSIBLE_ACTIONS[PRINT])
		return PRINT;
	else if (response == POSSIBLE_ACTIONS[START])
		return START;
	else if (response == POSSIBLE_ACTIONS[VOLUME])
		return VOLUME;
	else if (response == POSSIBLE_ACTIONS[SAVE])
		return SAVE;
	else if (response == POSSIBLE_ACTIONS[INITIALISE])
		return INITIALISE;
	else if (response == POSSIBLE_ACTIONS[HELP])
		return HELP;
	else if (response == POSSIBLE_ACTIONS[EXIT])
		return EXIT;
	else
		return UNRECOGNISED;*/

	for (int i = 0; i < POSSIBLE_ACTIONS_LENGTH; ++i)
		if (response.find(POSSIBLE_ACTIONS[i]) != std::wstring::npos)
			return InputOutcome(i);

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
			m_io.outputText(L"Invalid option received.");
			m_io.outputTextInline(L">> ");
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

	nChosen -= searchResults.songs.size();

	if (searchResults.playlists.size() > 0 && nChosen <= searchResults.playlists.size())
		m_mediaPlayer.addToAdHocQueue(searchResults.playlists.at(--nChosen));

	if (m_playerThread)
	{
		// might want to stop the mediaplayer first first..
		CloseHandle(m_playerThread->native_handle()); // yikes
	}
	m_playerThread = new std::thread(&MediaPlayer::playImmediate, m_mediaPlayer);

	if (m_mediaPlayer.getAdhocPlayback()->getSongList().size() >= 1)
		m_io.outputText(L"playing items..");
	else
		m_io.outputText(L"nothing to play..");

	handleHelpOutcome();
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
			m_io.outputText(L"Invalid option received.");
			m_io.outputTextInline(L">> ");
			nChosen = -1;
		}
	}

	size_t itemsAdded = 0;
	if (searchResults.artists.size() > 0 && nChosen <= searchResults.artists.size())
		itemsAdded = m_mediaPlayer.addToPlaybackQueue(searchResults.artists.at(--nChosen));
	
	nChosen -= searchResults.artists.size();

	if (searchResults.albums.size() > 0 && nChosen <= searchResults.albums.size())
		itemsAdded = m_mediaPlayer.addToPlaybackQueue(searchResults.albums.at(--nChosen));
	
	nChosen -= searchResults.albums.size();

	if (searchResults.songs.size() > 0 && nChosen <= searchResults.songs.size())
		itemsAdded = m_mediaPlayer.addToPlaybackQueue(searchResults.songs.at(--nChosen));

	nChosen -= searchResults.songs.size();

	if (searchResults.playlists.size() > 0 && nChosen <= searchResults.playlists.size())
		itemsAdded = m_mediaPlayer.addToPlaybackQueue(searchResults.playlists.at(--nChosen));

	wstring str = L"Successfully queued ";
	str += std::to_wstring(itemsAdded);
	str += L" items(s)";
	m_io.outputText(str);
}

void Controller::handlePrintOutcome()
{
	vector<Song> songList = m_mediaPlayer.getPlaybackQueue()->getSongList();

	m_io.outputNewline();
	m_io.outputHeading(L"   Queue   ");
	
	int index = 1;
	for (Song s : songList)
		m_io.outputText(std::to_wstring(index++) + L". " + s.getTitle() + L"(" + s.getAlbumTitle() + L") - " + s.getArtistName());

	m_io.outputNewline();
}

void Controller::handleStartOutcome()
{
	m_io.outputText(L"Playing queued items...");

	if (m_playerThread)
	{
		// might want to stop the mediaplayer first first..
		CloseHandle(m_playerThread->native_handle()); // yikes
	}
	m_playerThread = new std::thread(&MediaPlayer::playQueued, &m_mediaPlayer);
	//m_mediaPlayer.playQueued();
}

void Controller::handleVolumeOutcome(const wstring& volumeArgs)
{
	const int volume = std::stoi(volumeArgs);

	if (volume < 0)
	{
		m_io.outputText(L"volume cannot be less than 0 dess.");
		return;
	}
	else if (volume > 100)
	{
		m_io.outputText(L"volume cannot be greater than 100 dess.");
		return;
	}
	m_mediaPlayer.setVolume(volume);

	wstring str = L"Set volume to ";
	str += std::to_wstring(volume);
	str += L"%";
	m_io.outputText(str);
}

void Controller::handleSaveOutcome(const wstring& playlistTitle)
{
	m_io.outputTextInline(L"Saving playlist: " + playlistTitle + L"... ");

	if (m_musicLibrary.hasPlaylist(playlistTitle))
	{
		m_io.outputTextInline(L"Failed\nPlaylist with that title already exists.\n");

		m_io.outputText(L"Overwrite?\n1. Yes\n2. No (do nothing)\n");
		wstring chosen = L"";
		int nChosen = -1;
		while (nChosen <= 0 || nChosen > 2)
		{
			try
			{
				getline(wcin, chosen);
				nChosen = std::stoi(chosen);
			}
			catch (std::exception e)
			{
				m_io.outputText(L"Invalid option received.");
				m_io.outputTextInline(L">> ");
				nChosen = -1;
			}
		}

		if(nChosen == 2)
			return;
	}

	Playlist* queue = m_mediaPlayer.getPlaybackQueue();
	queue->setTitle(playlistTitle);
	m_musicLibrary.savePlaylist(*queue);
	m_io.outputTextInline(L"Done\n");
}

void Controller::handleInitialiseOutcome()
{
	m_io.outputTextWithSpacing(L"Performing library initialisation..");
	wstring response = L"";
	int nResponse = -1;

	bool setupSucc = firstTimeSetup();
	if (setupSucc)
	{
		m_io.outputTextWithSpacing(L"Setup success!");
		handleHelpOutcome();
		return;
	}
	else
	{
		m_io.outputTextWithSpacing(L"Setup failed...\n");
		m_io.outputText(L"Retry?\n1. Yes\n2. No (exit)");

		nResponse = getMenuOp(response);

		if (nResponse == 1)
		{
			handleInitialiseOutcome();
			return;
		}
		else
		{
			handleHelpOutcome();
			return;
		}
	}
}

void Controller::handleHelpOutcome()
{
	m_io.outputText(getMainMenuText());
}

void Controller::handleExitOutcome()
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

	m_io.outputTextWithSpacing(L"Artists Found: " + std::to_wstring(searchResults.artists.size()));
	for (Artist a : searchResults.artists)
		m_io.outputText(std::to_wstring(++maxOption) + L". " +
			a.getName());

	if (searchResults.artists.size() <= 0)
		m_io.outputText(L"<---  No results  --->");

	m_io.outputTextWithSpacing(L"Albums Found: " + std::to_wstring(searchResults.albums.size()));
	for (Album a : searchResults.albums)
		m_io.outputText(std::to_wstring(++maxOption) + L". " +
			a.getTitle() + L" - " + a.getArtistName());

	if (searchResults.albums.size() <= 0)
		m_io.outputText(L"<---  No results  --->");
	
	m_io.outputTextWithSpacing(L"Songs Found: " + std::to_wstring(searchResults.songs.size()));
	for (Song s : searchResults.songs)
		m_io.outputText(std::to_wstring(++maxOption) + L". " +
			s.getTitle() + L" (" + s.getAlbumTitle() + L") - " + s.getArtistName());

	if (searchResults.songs.size() <= 0)
		m_io.outputText(L"<---  No results  --->");

	m_io.outputTextWithSpacing(L"Playlists Found: " + std::to_wstring(searchResults.playlists.size()));
	for (Playlist p : searchResults.playlists)
		m_io.outputText(std::to_wstring(++maxOption) + L". " +
			p.getTitle() + L" (Songs: " + std::to_wstring(p.getSongList().size()) + L")");

	if (searchResults.playlists.size() <= 0)
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

		m_io.outputTextInline(L"\nChecking directory... ");
		filesFound = m_musicLibrary.populate(baseDir);

		if (!filesFound)
			m_io.outputText(L"No items found in directory. Please check the directory path is correct.");
	}

	return m_fileSystem.saveMusicLibrary(m_musicLibrary);
}
