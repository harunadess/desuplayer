#ifndef FRONTEND_H
#define FRONTEND_H

#include <string>
#include <vector>
#include <thread>

#include "ioHandler.h"
#include "FileSystem.h"
#include "musicLibrary.h"
#include "mediaPlayer.h"
#include "mpControls.h"
#include "ipc.h"

constexpr unsigned short POSSIBLE_ACTIONS_LENGTH = 10;

class Controller
{
public:
	Controller(MpControls& mpControls, IPC* ipc);
	~Controller();

	int init();
	bool firstTimeSetup();
	int main();

private:
	// todo: this needs refactored - there has to be a better way to map from strings to numbers
	enum InputOutcome
	{
		PLAY,
		SEARCH,
		QUEUE,
		PRINT,
		START,
		VOLUME,
		SAVE,
		INITIALISE,
		HELP,
		EXIT,
		UNRECOGNISED
	};

	const std::wstring POSSIBLE_ACTIONS[POSSIBLE_ACTIONS_LENGTH] =
	{
		std::wstring(L"play"),
		std::wstring(L"search"),
		std::wstring(L"queue"),
		std::wstring(L"print"),
		std::wstring(L"start"),
		std::wstring(L"volume"),
		std::wstring(L"save"),
		std::wstring(L"init"),
		std::wstring(L"help"),
		std::wstring(L"exit")
	};

	int getMenuOp(std::wstring& responseStr);
	int printSearchResults(SearchResults& searchResults);
	void handleResponse(const std::wstring& response);
	std::vector<std::wstring> parseResponse(const std::wstring& response) const;
	InputOutcome checkResponse(const std::wstring& response) const;
	bool fullSearch(const std::wstring& searchTerms, SearchResults& searchResults) const;

	// todo: refactor these (maybe)
	void handlePlayOutcome(const std::wstring& searchTerms, SearchResults& searchResults);
	void handleSearchOutcome(const std::wstring& searchTerms, SearchResults& searchResults);
	void handleQueueOutcome(const std::wstring& searchTerms, SearchResults& searchResults);
	
	void handlePrintOutcome();
	void handleStartOutcome();
	void handleVolumeOutcome(const std::wstring& volumeArgs);
	void handleSaveOutcome(const std::wstring& playlistTitle);
	void handleInitialiseOutcome();
	void handleHelpOutcome();
	void handleExitOutcome();

	IOHandler m_io;
	FileSystem m_fileSystem;
	MusicLibrary m_musicLibrary;
	MediaPlayer m_mediaPlayer;

	std::thread* m_playerThread;
};

#endif // !FRONTEND_H
