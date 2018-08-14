#include "FileSystem.h"

using std::filesystem::recursive_directory_iterator;
using std::wstring;

FileSystem::FileSystem()
{
}


FileSystem::~FileSystem()
{
}

bool isMusicFile(std::wstring extension)
{
	const wchar_t* includeList[4] = {L".mp3", L".flac", L".m4a", L".aac"}; //todo: move to private var
	unsigned int extensionLength = (sizeof (includeList) / sizeof (wchar_t*));

	for (unsigned int i = 0; i < extensionLength; i++)
	{
		if (extension.find(includeList[i]) != std::wstring::npos)
			return true;
	}
	return false;
}

void FileSystem::scanForNewFiles(const char* baseDir)
{
	for (auto& dirEntry : recursive_directory_iterator(baseDir))
	{
		try
		{
			if (dirEntry.is_regular_file())
			{
				if (isMusicFile(dirEntry.path().extension().wstring()))
				{
					wstring filename = dirEntry.path().filename().wstring();
					std::wcout << filename << std::endl; //todo: store this, or something
				}
			}
		}
		catch (const std::exception e)
		{
			std::wcout << "error:" << std::flush;
			std::wcout << e.what() << std::endl;
		}
	}
}
