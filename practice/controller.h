#ifndef FRONTEND_H
#define FRONTEND_H

#include <string>
#include <vector>

#include "ioHandler.h"
#include "FileSystem.h"
#include "musicLibrary.h"
#include "mediaPlayer.h"

constexpr unsigned short POSSIBLE_ACTIONS_LENGTH = 8;

class Controller
{
public:
	Controller();
	~Controller();

	int init();
	bool firstTimeSetup();
	int main();

private:
	enum InputOutcome
	{
		UNRECOGNISED,
		PLAY,
		SEARCH,
		QUEUE,
		PRINT,
		START,
		SAVE,
		HELP,
		EXIT
	};

	const std::wstring POSSIBLE_ACTIONS[POSSIBLE_ACTIONS_LENGTH] = 
	{
		std::wstring(L"play"),
		std::wstring(L"search"),
		std::wstring(L"queue"),
		std::wstring(L"print"),
		std::wstring(L"start"),
		std::wstring(L"save"),
		std::wstring(L"help"),
		std::wstring(L"exit")
	};

	int printSearchResults(SearchResults& searchResults);
	void handleResponse(const std::wstring& response);
	std::vector<std::wstring> parseResponse(const std::wstring& response) const;
	InputOutcome checkResponse(const std::wstring& response) const;
	bool fullSearch(const std::wstring& searchTerms, SearchResults& searchResults) const;
	void handlePlayOutcome(const std::wstring& searchTerms, SearchResults& searchResults);
	void handleSearchOutcome(const std::wstring& searchTerms, SearchResults& searchResults);
	void handleQueueOutcome(const std::wstring& searchTerms, SearchResults& searchResults);
	void handlePrintOutcome();
	void handleStartOutcome();
	void handleSaveOutcome(const std::wstring& playlistTitle);
	void handleHelpOutcome();
	void handleExitOutcome();

	IOHandler m_io;
	FileSystem m_fileSystem;
	MusicLibrary m_musicLibrary;
	MediaPlayer m_mediaPlayer;
};



#endif // !FRONTEND_H
