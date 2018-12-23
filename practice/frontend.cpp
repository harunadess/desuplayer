#include "frontend.h"

#include "ioHandler.h"

using std::getline;

FrontEnd::FrontEnd()
{
}

FrontEnd::~FrontEnd()
{
}

const wstring getMainMenuText()
{
	wstring s = L"\n\n";
	s += L"Type \"play\" followed by an item to play any song, artist, album, playlist or the queue.";
	s += L"Type \"search\" followed by search criteria to find and print that item to the window.";
	s += L"Type \"queue\" to see songs currently in the queue.";
	s += L"Type \"help\" to get help.\n";
	s += L"Type \"exit\" to exit the application.";

	return s;
}

int FrontEnd::main(int argc, wchar_t* argv[])
{
	IOHandler io;
	io.outputHeading(L"Console Music Player");
	wstring response = L"";
	while (true)
	{
		io.outputText(getMainMenuText());
		getline(wcin, response);

		handleResponse(response);
	}

	return 0;
}

void FrontEnd::handleResponse(const wstring& response)
{
	vector<wstring> parsedResponse = vector<wstring>();
	parsedResponse = parseResponse(response);
	InputOutcome outcome = checkResponse(parsedResponse[0]);
	switch (outcome)
	{
	case InputOutcome::PLAY:
		//todo play thing here
		break;
	case InputOutcome::SEARCH:
		//todo search
		break;
	case InputOutcome::QUEUE:
		//todo queue
		break;
	case InputOutcome::HELP:
		//todo help
		break;
	case InputOutcome::EXIT:
		exit(0);
		break;
	case InputOutcome::UNRECOGNISED:
	default:
		//todo handle unknown action
		break;
	}
}

vector<wstring> FrontEnd::parseResponse(const wstring& response) const
{
	vector<wstring> inputWords = vector<wstring>();
	wstring word = L"";
	for (int i = 0; i < response.size(); i++)
	{
		if (response.compare(i, 1, L" "))
			word += inputWords[i];
		else
		{
			inputWords.push_back(word);
			word = L"";
		}
	}
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
