#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <fstream>
#include "filePath.h"
#include "musicLibrary.h"

constexpr unsigned int INCLUDE_LIST_LENGTH = 5;

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
	bool saveMusicLibrary(const MusicLibrary& musicLibrary);
	bool loadMusicLibrary(MusicLibrary& musicLibrary);
	
private:
	const char* includeList_[INCLUDE_LIST_LENGTH] = { ".mp3", ".flac", ".m4a", ".aac", ".ogg" };
	bool isMusicFile(string extension);

};

#endif // !FILESYSTEM_H
