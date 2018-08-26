#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <iostream>
#include "FilePath.h"

using std::string;
using std::wstring;
using std::vector;
using std::filesystem::recursive_directory_iterator;

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	vector<FilePath> scanForNewFiles(wstring baseDir);

private:
	bool isMusicFile(string);

	const char* includeList_[5] = { ".mp3", ".flac", ".m4a", ".aac", ".ogg" };
	const unsigned short includeListLength_ = (sizeof(includeList_) / sizeof(char*));

};

#endif // !FILESYSTEM_H
