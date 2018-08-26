#include "filePath.h"

FilePath::FilePath()
{
}

FilePath::FilePath(std::wstring wideFilePath, std::string u8FilePath)
{
	this->wideFilePath_ = wideFilePath;
	this->u8FilePath_ = u8FilePath;
}
