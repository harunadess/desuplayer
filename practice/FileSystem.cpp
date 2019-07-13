#include "fileSystem.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

bool FileSystem::saveMusicLibrary(const MusicLibrary& musicLibrary)
{
	std::ofstream fileOut(LIBRARY_FILE_NAME, std::ios::binary);

	if (!fileOut.is_open())
		return false;

	try
	{
		// todo: make directory for file to go into or something
		cereal::BinaryOutputArchive outputArchive(fileOut);
		outputArchive(musicLibrary);

		fileOut.close();
		return true;
	}
	catch (std::exception e)
	{
		fileOut.close();
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
		fileIn.close();
		return false;
	}
}
