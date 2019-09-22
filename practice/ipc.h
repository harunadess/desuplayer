#ifndef IPC_H
#define IPC_H

#include <Windows.h>
#include <iostream>

const int BUFFER_SIZE = 4096;

class IPC
{
public:
	IPC(HANDLE* hStdIn);
	~IPC();

	void writeToPipe(const std::wstring& str);

private:
	HANDLE* m_hStdIn;
};

#endif // !IPC_H
