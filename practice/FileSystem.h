#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>
#include <iostream>

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	void scanForNewFiles(const char* baseDir);
private:

};

#endif // !FILESYSTEM_H
