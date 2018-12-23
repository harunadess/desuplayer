#ifndef FRONTEND_H
#define FRONTEND_H

#include <string>
#include <vector>
using std::wstring;
using std::vector;

constexpr unsigned short POSSIBLE_ACTIONS = 5;

class FrontEnd
{
public:
	FrontEnd();
	~FrontEnd();

	int main(int argc, wchar_t* argv[]);

private:
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

	void handleResponse(const wstring& response);
	vector<wstring> parseResponse(const wstring& response) const;
	InputOutcome checkResponse(const wstring& response) const;

};


#endif // !FRONTEND_H
