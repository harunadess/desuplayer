#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <fstream>

#include "filePath.h"
#include "musicLibrary.h"

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	bool saveMusicLibrary(const MusicLibrary& musicLibrary);
	bool loadMusicLibrary(MusicLibrary& musicLibrary);
	
private:
	const std::wstring LIBRARY_FILE_NAME = L"library.desu";

};

#endif // !FILESYSTEM_H
