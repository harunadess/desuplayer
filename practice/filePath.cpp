#include "filePath.h"

FilePath::FilePath()
{
}

SongFormat determineFormat(std::string u8FilePath)
{
	const int FORMATS = 4;
	std::string formats[4] = { ".mp3", ".flac", ".aac", ".ogg" };

	for (int i = 0; i < FORMATS; i++)
		if (u8FilePath.find(formats[i]) != std::string::npos)
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
