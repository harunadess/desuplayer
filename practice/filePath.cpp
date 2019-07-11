#include "filePath.h"

FilePath::FilePath()
{
}

FilePath::FilePath(std::wstring wideFilePath, std::string u8FilePath)
	:wideFilePath(wideFilePath), u8FilePath(u8FilePath)
{
}

FilePath::~FilePath()
{
}
