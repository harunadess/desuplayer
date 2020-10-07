#include "filePath.h"

FilePath::FilePath()
{
}

SongFormat determineFormat(std::string u8FilePath)
{
	for (int i = 0; i < NUM_EXTENSIONS; i++)
		if (u8FilePath.find(SongExtensions[i]) != std::string::npos)
			return SongFormat(i);

	return MP3;
}

FilePath::FilePath(std::wstring wideFilePath, std::string u8FilePath)
	:wideFilePath(wideFilePath), u8FilePath(u8FilePath)
{
	format = determineFormat(u8FilePath);
}

FilePath::~FilePath()
{
}
