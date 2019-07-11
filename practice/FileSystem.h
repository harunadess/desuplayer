#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <fstream>

#include "filePath.h"
#include "musicLibrary.h"

//constexpr unsigned int INCLUDE_LIST_LENGTH = 5;

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	//std::vector<FilePath> scanForNewFiles(std::wstring baseDir);
	bool saveMusicLibrary(const MusicLibrary& musicLibrary);
	bool loadMusicLibrary(MusicLibrary& musicLibrary);
	
private:
	//const char* m_INCLUDE_LIST[INCLUDE_LIST_LENGTH] = { ".mp3", ".flac", ".m4a", ".aac", ".ogg" };

	//bool isMusicFile(std::string extension);

	const std::wstring LIBRARY_FILE_NAME = L"library.desu";

};

#endif // !FILESYSTEM_H
