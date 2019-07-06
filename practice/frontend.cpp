#include "frontend.h"

using std::getline;

FrontEnd::FrontEnd()
{
	bool loadSucc = fileSystem_.loadMusicLibrary(musicLibrary_);
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

const wstring getMainMenuText()
{
	wstring s = L"\n\n";
	s += L"Type \"play\" followed by an item to play any song, artist, album, playlist or the queue.\n";
	s += L"Type \"search\" followed by search criteria to find and print results to the window.\n";
	s += L"Type \"queue\" to see songs currently in the queue.\n";
	s += L"Type \"help\" to get help.\n";
	s += L"Type \"exit\" to exit the application.\n";

	return s;
}

int FrontEnd::main()
{
	io_.outputHeading(L"Console Music Player");
	
	wstring response = L"";
	wstring output = L"";
	io_.outputText(getMainMenuText());
	while (true)
	{
		io_.outputTextInline(L">> ");
		getline(wcin, response);

		output = handleResponse_(response);

		io_.outputTextWithSpacing(output);
	}

	return 0;
}

wstring FrontEnd::handleResponse_(const wstring& response)
{
	vector<wstring> parsedResponse = parseResponse_(response);
	InputOutcome outcome = checkResponse_(parsedResponse[0]);
	
	size_t parsedResponseLen = parsedResponse[0].length();

	wstring searchTerms = response;
	searchTerms = searchTerms.replace(searchTerms.begin(), (searchTerms.begin() + parsedResponseLen + 1), L"");

	SearchResults searchResults;
	bool succ = true;

	switch (outcome)
	{
	case InputOutcome::PLAY:
		// play immediate
		
		succ = unifiedSearch_(searchTerms, searchResults);
		wcout << L"Search success: " << succ << endl;
		if (!succ)
			return L"Error in library search";

		break;
	case InputOutcome::SEARCH:
		// just search for things
		succ = unifiedSearch_(searchTerms, searchResults);
		wcout << L"Search success: " << succ << endl;
		if (!succ)
			return L"Error in library search";

		printSearchResults_(searchResults);

		break;
	case InputOutcome::QUEUE:
		// add to mp queue
		succ = unifiedSearch_(searchTerms, searchResults);
		wcout << L"Search success: " << succ << endl;
		if (!succ)
			return L"Error in library search";

		break;
	case InputOutcome::HELP:
		// print help
		io_.outputText(getMainMenuText());
		break;
	case InputOutcome::EXIT:
		wcout << flush;
		exit(0);
		break;
	case InputOutcome::UNRECOGNISED:
	default:
		return L"Unrecognised action. Use 'help' command for usage info.";
		break;
	}

	return L"";
}

vector<wstring> FrontEnd::parseResponse_(const wstring& response) const
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

FrontEnd::InputOutcome FrontEnd::checkResponse_(const wstring& response) const
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

bool FrontEnd::unifiedSearch_(const wstring& searchTerms, SearchResults& searchResults) const
{
	bool success = true;
	//todo: search each of
	// Aritst
	// Album
	// Songs
	// return anything that partially matches search terms
	// i.e. "Anfang" should return the album by Roselia
	// *ideally "Roselia - Anfang" would also return that
	//		however, should not return *anything* by Roselia
	// searching "Origin" would return the Song and the Album
	success = musicLibrary_.unifiedSearch(searchTerms, searchResults);
	return success;
}

void FrontEnd::printSearchResults_(const SearchResults& searchResults)
{
	io_.outputTextWithSpacing(L"Artists Found: ");
	for (Artist a : searchResults.artists)
		io_.outputText(a.getName());

	if (searchResults.artists.size() <= 0)
		io_.outputText(L"<---  No results  --->");

	io_.outputTextWithSpacing(L"Albums Found: ");
	for (Album a : searchResults.albums)
		io_.outputText((a.getTitle() + L" - " + a.getArtistName()));

	if (searchResults.albums.size() <= 0)
		io_.outputText(L"<---  No results  --->");
	
	io_.outputTextWithSpacing(L"Songs Found: ");
	for (Song s : searchResults.songs)
		io_.outputText((s.getTitle() + L"(" + s.getAlbum() + L") - " + s.getArtist()));

	if (searchResults.songs.size() <= 0)
		io_.outputText(L"<---  No results  --->");
}


// May not be neeeded or desired.

//void clearConsole(char fill = ' ') {
//	COORD tl = { 0,0 };
//	CONSOLE_SCREEN_BUFFER_INFO s;
//	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//	GetConsoleScreenBufferInfo(console, &s);
//	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
//	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
//	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
//	SetConsoleCursorPosition(console, tl);
//}
