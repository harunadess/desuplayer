#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <vector>
#include <wchar.h>

using std::wcout; //use "wide" cout and cin to allow for UTF-8 characters
using std::endl;
using std::wstring;
using std::vector;

void printUsage()
{
	wstring s = L"\n\n";
	s += L"Usage: mp <command> arg <flags>\n\n";
	s += L"Commands:\n";
	s += L"-artist\t Find all songs by artists matching argument\n";
	s += L"-album\t Find all songs from an album matching argument\n";
	s += L"-song\t Find all songs matching argument\n\n";
	s += L"-queue\t Show all songs currently in queue\n\n";
	s += L"-Flags:\n";
	s += L"--p\t play immediately\n";
	s += L"--q\t add to queue";
	s += L"--s\t pause playback";
	s += L"--flush\t flush queue and stop playback\n";

	wcout << s << endl;
}

void processCommand(vector<const wchar_t*> args)
{
	wcout << "process command" << endl;

}

void processIntent(int argc, wchar_t* argv[])
{
	vector<const wchar_t*> args;
	wstring arg = L"";

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
		{
			arg.append(argv[i]);
			arg.append(L" ");
		}
		else
		{
			const wchar_t* c_arg = arg.c_str();
			if(arg.size() > 1)
				args.push_back(c_arg);
			args.push_back(argv[i]);
		}
	}

	for (int i = 0; i < args.size(); i++)
		wcout << i << " " << args.at(i) << endl;

	processCommand(args);
}

int wmain(int argc, wchar_t* argv[])
{
	if (argc == 0)
	{
		printUsage();
	}
	else
	{
		processIntent(argc, argv);
	}

	return 0;
}