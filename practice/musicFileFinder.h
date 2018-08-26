#ifndef MUSICFILEFINDER_H
#define MUSICFILEFINDER_H

#include <filesystem>
#include <iostream>
#include "filePath.h"

using std::string;
using std::wstring;
using std::vector;
using std::filesystem::recursive_directory_iterator;

class MusicFileFinder
{
public:
	MusicFileFinder();
	~MusicFileFinder();

	vector<FilePath> scanForNewFiles(wstring baseDir);

private:
	bool isMusicFile(string fileExtension);

	const char* includeList_[5] = { ".mp3", ".flac", ".m4a", ".aac", ".ogg" };
	const unsigned short includeListLength_ = (sizeof(includeList_) / sizeof(char*));

};

#endif // !MUSICFILEFINDER_H
