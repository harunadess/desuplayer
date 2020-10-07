#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <thread>

#include "mpControls.h"
#include "controller.h"

// piping
HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
// child process
STARTUPINFOW si;
PROCESS_INFORMATION pi;
// kb hook
HHOOK g_hKeyboard_LL = NULL;
KBDLLHOOKSTRUCT g_kbdStruct;
// thread for hooking
HANDLE hKbhThread;
std::thread kbhThread;
// needed here so keyboardProc can manipulate it - ptr passed to mediaPlayer
MpControls mpControls;
// need to create IPC here so we can use global handles
IPC ipc(&g_hChildStd_IN_Wr);

void configConsole()
{
	//Set CodePage of console so it will be UTF-8 encoded
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	_setmode(_fileno(stdout), _O_U8TEXT);

	CONSOLE_FONT_INFOEX consoleFontInfo;
	consoleFontInfo.cbSize = (sizeof consoleFontInfo);
	consoleFontInfo.nFont = 0;
	consoleFontInfo.dwFontSize.X = 8;
	consoleFontInfo.dwFontSize.Y = 14; //main font size control (pt)
	consoleFontInfo.FontFamily = FF_DONTCARE;
	consoleFontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(consoleFontInfo.FaceName, L"MS Gothic"); //set font type, ms gothic seems to support most unicode characters

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFontInfo);
}

//todo: need to fix non-initial program startup
// -> library scan to update library

// -> m4a files (is it even possible?)
// -> honour disc numbers
// -> more fields to songs - genre, disc number(? - not pulled with taglib???), format


bool configPipe()
{
	bool succ = false;

	// set pipe handles to be inherited
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// create pipe for child STDIN Rd
	succ = CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0);

	if (!succ)
		return succ;

	// don't want STD_IN Wr handle to be inherited 
	succ = SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0);

	return succ;
}

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			g_kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			switch (g_kbdStruct.vkCode)
			{
			case VK_MEDIA_PLAY_PAUSE:
				mpControls.pause.store(true);
				break;
			case VK_MEDIA_NEXT_TRACK:
				mpControls.next.store(true);
				break;
			case VK_MEDIA_PREV_TRACK:
				mpControls.prev.store(true);
				break;
			case VK_MEDIA_STOP:
				mpControls.stop.store(true);
				break;
			case VK_ESCAPE:
				mpControls.exit.store(true);
				break;
			}
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

DWORD WINAPI threadProcMsgLoop()
{
	// thread running needs to create hook and use message loop
	g_hKeyboard_LL = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
	if (!g_hKeyboard_LL)
		wprintf(L"failed to install keyboard hook\n");

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

bool configGlobalKbHook()
{
	hKbhThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&threadProcMsgLoop, NULL, 0, NULL);

	return (hKbhThread != NULL);
}

bool createChildProcess()
{
	wchar_t cmdl[] = L"dess.exe";

	bool succ = false;
	
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	memset(&si, 0, sizeof(STARTUPINFOW));
	
	si.cb = sizeof(STARTUPINFOW);
	si.hStdInput = g_hChildStd_IN_Rd;		// use created pipe for input
	si.dwFlags |= STARTF_USESTDHANDLES;

	succ = CreateProcessW(
		NULL,							//lpApplicationName
		cmdl,							//lpCommandLine
		NULL,							//lpProcessAttributes
		NULL,							//lpThreadAttributes
		TRUE,							//bInheritHandles - yes
		CREATE_NEW_CONSOLE,				//dwCreationFlags - new console pls
		NULL,							//lpEnvironment - use parent
		NULL,							//lpCurrentDirectory - use parent
		&si,							//lpStartupInfo
		&pi								//lpProcessInformation
	);

	return succ;
}

/*
	1. Create pipe to child process
	2.Set up global keyboard hook (create thread w/ msg loop)
	3. Create child process
*/
bool programSetup()
{
	bool succ = false;

	succ = configPipe();
	if (!succ)
	{
		wprintf(L"Error setting up IPC.\n");
		return false;
	}

	succ = configGlobalKbHook();
	if (!succ)
	{
		wprintf(L"Error creating keyboard hook.\n");
		return false;
	}

	succ = createChildProcess();
	if (!succ)
	{
		wprintf(L"Error creating child dess.\n");
		return false;
	}

	return true;
}

bool cleanUp()
{
	bool succ = false;

	// Close pipe handle so child process stops reading
	succ = CloseHandle(g_hChildStd_IN_Wr);
	
	if (!succ)
	{
		wprintf(L"Error closing Std_IN_Wr handle.\n");

		if (kbhThread.joinable())
			kbhThread.join();

		CloseHandle(hKbhThread);
		return false;
	}

	// Close thread
	if (kbhThread.joinable())
		kbhThread.join();

	succ = CloseHandle(hKbhThread);

	if (!succ)
	{
		wprintf(L"Error closing hook thread handle.\n");
		return false;
	}

	succ = CloseHandle(pi.hProcess);

	if (!succ)
	{
		wprintf(L"Error closing hook thread handle.\n");
		return false;
	}

	return true;
}


/**
	TODO:
		- fix release version
			- icon
			- signage (laptop)
*/

int wmain(int argc, wchar_t* argv[])
{
	configConsole();

	bool succ = programSetup();

	if (!succ)
		return 1;

	Controller* controller = new Controller(mpControls, &ipc);
	int controllerCode = controller->init();

	if(controllerCode == 0)
		controllerCode = controller->main();
	
	succ = cleanUp();

	if (!succ)
		return 1;

	return controllerCode;
}
