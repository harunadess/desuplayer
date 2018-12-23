#include "fileSystem.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#define LIBRARY_FILE_NAME L"library.desu"

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

bool FileSystem::isMusicFile(string extension)
{
	for (unsigned int i = 0; i < INCLUDE_LIST_LENGTH; i++)
	{
		if (extension.find(includeList_[i]) != string::npos)
			return true;
	}
	return false;
}

vector<FilePath> FileSystem::scanForNewFiles(wstring baseDir)
{
	try
	{
		vector<FilePath> foundFiles;
		for (auto& dirEntry : recursive_directory_iterator(baseDir))
		{
			if (dirEntry.is_regular_file())
			{
				if (isMusicFile(dirEntry.path().extension().u8string()))
				{
					FilePath filePath(dirEntry.path().wstring(), dirEntry.path().u8string());
					foundFiles.push_back(filePath);
				}
			}
		}
		return foundFiles;
	}
	catch (const std::filesystem::filesystem_error e)
	{
		return vector<FilePath>();
	}
	catch (const std::exception e)
	{
		printf_s("%s: %s\n", "Unexpected error scanning for files", e.what());
		exit(1);
	}
}

bool FileSystem::saveMusicLibrary(const MusicLibrary& musicLibrary)
{
	std::ofstream fileOut(LIBRARY_FILE_NAME, std::ios::binary);
	if (!fileOut.is_open())
		return false;

	try
	{
		cereal::BinaryOutputArchive outputArchive(fileOut);
		outputArchive(musicLibrary);
		fileOut.close();
		return true;
	}
	catch (std::exception e)
	{
		return false;
	}
}

bool FileSystem::loadMusicLibrary(MusicLibrary& musicLibrary)
{
	std::ifstream fileIn(LIBRARY_FILE_NAME, std::ios::binary);
	if (!fileIn.is_open())
		return false;

	try
	{
		cereal::BinaryInputArchive inputArchive(fileIn);
		inputArchive(musicLibrary);
		fileIn.close();
		return true;
	}
	catch (std::exception e)
	{
		return false;
	}
	
}