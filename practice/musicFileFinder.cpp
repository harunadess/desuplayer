#include "musicFileFinder.h"

MusicFileFinder::MusicFileFinder()
{
}

MusicFileFinder::~MusicFileFinder()
{
}

bool MusicFileFinder::isMusicFile(string extension)
{
	for (unsigned int i = 0; i < includeListLength_; i++)
	{
		if (extension.find(includeList_[i]) != string::npos)
			return true;
	}
	return false;
}

wstring normaliseDirString(wstring& baseDir)
{
	wstring newDir = L"";
	for(wstring::iterator it = baseDir.begin(); it != baseDir.end(); ++it) 
	{
		if (*it == L'/' || *it == std::filesystem::path::preferred_separator)
			newDir += std::filesystem::path::preferred_separator;
		else
			newDir += *it;
	}
	
	if(newDir.back() != std::filesystem::path::preferred_separator)
		newDir += std::filesystem::path::preferred_separator;

	return newDir;
}

vector<FilePath> MusicFileFinder::scanForNewFiles(wstring baseDir)
{
	try
	{
		baseDir = normaliseDirString(baseDir);
		vector<FilePath> foundFiles;
		for (auto& dirEntry : recursive_directory_iterator(baseDir))
		{
			if (dirEntry.is_regular_file())
			{
				if (isMusicFile(dirEntry.path().extension().u8string().c_str()))
				{
					FilePath fpObj(dirEntry.path().wstring(), dirEntry.path().u8string());
					foundFiles.push_back(fpObj);
				}
			}
		}
		return foundFiles;
	}
	catch (const std::filesystem::filesystem_error e)
	{
		std::wcerr << "FileSystem error: " << e.what() << std::endl;
		return vector<FilePath>();
	}
	catch (const std::exception e)
	{
		std::wcerr << "Big error scanning for files: " << e.what() << std::endl;
		exit(1);
	}
}