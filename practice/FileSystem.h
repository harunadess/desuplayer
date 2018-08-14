#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <iostream>

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	bool scanForNewFiles(wchar_t* baseDir);
private:

};

#endif // !FILESYSTEM_H
