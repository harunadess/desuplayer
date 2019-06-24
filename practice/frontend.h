#ifndef FRONTEND_H
#define FRONTEND_H

#include <string>
#include <vector>

#include "ioHandler.h"
#include "FileSystem.h"
#include "musicLibrary.h"

using std::wstring;
using std::vector;

constexpr unsigned short POSSIBLE_ACTIONS = 5;

class FrontEnd
{
public:
	FrontEnd();
	~FrontEnd();

	int main();

private:
	IOHandler io_;
	FileSystem fileSystem_;
	MusicLibrary musicLibrary_;

	void printSearchResults_(const SearchResults& searchResults);

	enum InputOutcome
	{
		UNRECOGNISED,
		PLAY,
		SEARCH,
		QUEUE,
		HELP,
		EXIT
	};

	const wstring PossibleActions[POSSIBLE_ACTIONS] = 
	{
		wstring(L"play"),
		wstring(L"search"),
		wstring(L"queue"),
		wstring(L"help"),
		wstring(L"exit")
	};

	wstring handleResponse_(const wstring& response);
	vector<wstring> parseResponse_(const wstring& response) const;
	InputOutcome checkResponse_(const wstring& response) const;
	bool unifiedSearch_(const wstring& searchTerms, SearchResults& searchResults) const;

};



#endif // !FRONTEND_H
