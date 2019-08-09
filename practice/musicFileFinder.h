#ifndef MUSICFILEFINDER_H
#define MUSICFILEFINDER_H

#include <filesystem>
#include <iostream>

#include "filePath.h"

//constexpr unsigned int INCLUDE_LIST_LENGTH = 5;
constexpr unsigned int INCLUDE_LIST_LENGTH = 4;

class MusicFileFinder
{
public:
	MusicFileFinder();
	~MusicFileFinder();

	std::vector<FilePath> scanForNewFiles(std::wstring& baseDir);

private:
	bool isMusicFile(std::string fileExtension);

	//const char* m_INCLUDE_LIST[INCLUDE_LIST_LENGTH] = { ".mp3", ".flac", ".m4a", ".aac", ".ogg" };
	const char* m_INCLUDE_LIST[INCLUDE_LIST_LENGTH] = { ".mp3", ".flac", ".aac", ".ogg" };

};

#endif // !MUSICFILEFINDER_H
