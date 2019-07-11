#include "frontend.h"

using std::wstring;
using std::vector;
using std::map;
using std::wcin;
using std::wcout;
using std::endl;
using std::flush;
using std::getline;

FrontEnd::FrontEnd()
{
	bool loadSucc = m_fileSystem.loadMusicLibrary(m_musicLibrary);
	if (!loadSucc)
	{
		wcout << L"Failed to load library." << endl;
		// todo: need to find and load music from dirs.
	}
	wcout << L"Successfully loaded library" << endl;
}

FrontEnd::~FrontEnd()
{
}

//todo: how do you populate/add things/view playlists??
const wstring getMainMenuText()
{
	wstring s = L"\n\n";
	s += L"Type \"play\" followed by an item to play any song, artist, album, playlist or the queue.\n";
	s += L"Type \"search\" followed by search criteria to find and print results to the window.\n";
	s += L"Type \"queue\" to see songs currently in the queue.\n";
	s += L"Type \"help\" to print this text.\n";
	s += L"Type \"exit\" to exit the application.\n";

	return s;
}

int FrontEnd::main()
{
	m_io.outputHeading(L"Console Music Player");
	
	wstring response = L"";
	wstring output = L"";
	m_io.outputText(getMainMenuText());
	while (true)
	{
		m_io.outputTextInline(L">> ");
		getline(wcin, response);

		handleResponse(response);
	}

	return 0;
}

void FrontEnd::handleResponse(const wstring& response) //todo: convert handle<x>Outcome functions to use m_io 
{
	vector<wstring> parsedResponse = parseResponse(response);
	InputOutcome outcome = checkResponse(parsedResponse[0]);
	
	size_t parsedResponseLen = parsedResponse[0].length();

	wstring searchTerms = response;
	searchTerms = searchTerms.replace(searchTerms.begin(), (searchTerms.begin() + parsedResponseLen + 1), L"");

	SearchResults searchResults;

	switch (outcome)
	{
	case InputOutcome::PLAY:
		// play immediate
		handlePlayOutcome(searchTerms, searchResults);
		break;
	case InputOutcome::SEARCH:
		// just search for things
		handleSearchOutcome(searchTerms, searchResults);
		break;
	case InputOutcome::QUEUE:
		// add to mp queue
		handleQueueOutcome(searchTerms, searchResults);
		break;
	case InputOutcome::HELP:
		// print help
		handleHelpOutcome(searchTerms, searchResults);
		break;
	case InputOutcome::EXIT:
		handleExitOutcome(searchTerms, searchResults);
		break;
	case InputOutcome::UNRECOGNISED:
	default:
		wcout << L"Unrecognised action. Use 'help' command for usage info." << endl;
		break;
	}
}

void FrontEnd::handlePlayOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	bool succ = fullSearch(searchTerms, searchResults);
	wcout << L"Search success: " << succ << endl;
	if (!succ)
		wcout << L"Error in library search" << endl;

	int maxOption = printSearchResults(searchResults);
	wstring chosen = L"";

	int nChosen = -1;
	wcout << L"Enter a number from the search results, or -1 to exit.\n>> " << flush;
	
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
			wcout << L"Invalid option received: " << e.what() << endl;
			nChosen = -1;
		}
	}

	//todo: play thing at whatever position;
	if (searchResults.artists.size() > 0 && nChosen <= searchResults.artists.size())
	{
		m_mediaPlayer.addToPlaybackQueue(searchResults.artists.at(--nChosen));
	}
	nChosen -= searchResults.artists.size();

	if (searchResults.albums.size() > 0 && nChosen <= searchResults.albums.size())
	{
		m_mediaPlayer.addToPlaybackQueue(searchResults.albums.at(--nChosen));
	}
	nChosen -= searchResults.albums.size();

	if (searchResults.songs.size() > 0 && nChosen <= searchResults.songs.size())
	{
		m_mediaPlayer.addToPlaybackQueue(searchResults.songs.at(--nChosen));
	}

	m_mediaPlayer.playQueued();
	
}

void FrontEnd::handleSearchOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	bool succ = fullSearch(searchTerms, searchResults);
	wcout << L"Search success: " << (succ == 1 ? L"true" : L"false") << endl;
	if (!succ)
		wcout << L"Error in library search" << endl;

	printSearchResults(searchResults);
}

void FrontEnd::handleQueueOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	bool succ = fullSearch(searchTerms, searchResults);
	wcout << L"Search success: " << succ << endl;
	if (!succ)
		wcout << L"Error in library search" << endl;
}

void FrontEnd::handleHelpOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	m_io.outputText(getMainMenuText());
}

void FrontEnd::handleExitOutcome(const wstring& searchTerms, SearchResults& searchResults)
{
	wcout << flush;
	exit(0);
}

vector<wstring> FrontEnd::parseResponse(const wstring& response) const
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

	if(word != L"")
		inputWords.push_back(word);

	return inputWords;
}

FrontEnd::InputOutcome FrontEnd::checkResponse(const wstring& response) const
{
	if (response == PossibleActions[0])
		return InputOutcome::PLAY;
	else if (response == PossibleActions[1])
		return InputOutcome::SEARCH;
	else if (response == PossibleActions[2])
		return InputOutcome::QUEUE;
	else if (response == PossibleActions[3])
		return InputOutcome::HELP;
	else if (response == PossibleActions[4])
		return InputOutcome::EXIT;
	else
		return InputOutcome::UNRECOGNISED;
}

bool FrontEnd::fullSearch(const wstring& searchTerms, SearchResults& searchResults) const
{
	return m_musicLibrary.fullSearch(searchTerms, searchResults);
}

int FrontEnd::printSearchResults(SearchResults& searchResults)
{
	int maxOption = 0;
	m_io.outputTextWithSpacing(L"Artists Found: ");
	for (Artist a : searchResults.artists)
	{
		wcout << ++maxOption << L". " << flush;
		m_io.outputTextInline(a.getName());
		m_io.outputNewline();
	}

	if (searchResults.artists.size() <= 0)
		m_io.outputText(L"<---  No results  --->");

	m_io.outputTextWithSpacing(L"Albums Found: ");
	for (Album a : searchResults.albums)
	{
		wcout << ++maxOption << L". " << flush;
		m_io.outputTextInline((a.getTitle() + L" - " + a.getArtistName()));
		m_io.outputNewline();
	}

	if (searchResults.albums.size() <= 0)
		m_io.outputText(L"<---  No results  --->");
	
	m_io.outputTextWithSpacing(L"Songs Found: ");
	for (Song s : searchResults.songs)
	{
		wcout << ++maxOption << L". " << flush;
		m_io.outputText((s.getTitle() + L"(" + s.getAlbumTitle() + L") - " + s.getArtistName()));
		m_io.outputNewline();
	}

	if (searchResults.songs.size() <= 0)
		m_io.outputText(L"<---  No results  --->");

	return maxOption;
}
