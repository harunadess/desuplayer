#include "ipc.h"

IPC::IPC(HANDLE* hStdIn)
	:m_hStdIn(hStdIn)
{
}

IPC::~IPC()
{
}

void IPC::writeToPipe(const std::wstring& str)
{
	std::wstring msg = str;
	msg.append(L"\n");

	DWORD dwToWrite, dwWritten;
	wchar_t chBuf[BUFFER_SIZE];

	lstrcpyW(chBuf, msg.c_str());
	dwToWrite = (DWORD)(sizeof(wchar_t)*(msg.size() + 1));

	bool succ = false;
	succ = WriteFile(*m_hStdIn, (LPCVOID)chBuf, dwToWrite, &dwWritten, NULL);

	if (!succ || dwWritten == 0)
		wprintf(L"Failed to write to pipe\n");
}
