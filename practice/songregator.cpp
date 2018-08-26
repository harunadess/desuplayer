#include "songregator.h"

Songregator::Songregator()
{
}

Songregator::~Songregator()
{
}

vector<FilePath> scanForMusicFiles(const wstring& baseDir)
{
	MusicFileFinder finder;
	vector<FilePath> files = finder.scanForNewFiles(baseDir);

	return files;
}

bool Songregator::createSongList(const wstring& baseDir, vector<Song>& songList)
{
	vector<FilePath> filePaths = scanForMusicFiles(baseDir);
	if (filePaths.size() <= 0)
		return false;

	FileRef fileRef;
	Tag* tag = nullptr;
	for (const FilePath& fp : filePaths)
	{
		fileRef = FileRef(fp.wideFilePath_.c_str());
		if (!fileRef.isNull() && fileRef.tag())
		{
			try
			{
				tag = fileRef.tag();
				songList.push_back(createSong(tag, fp));
			}
			catch (std::exception e)
			{
				std::wcerr << ("%s - (%d):", __FILE__, __LINE__) << e.what() << std::endl;
				//return false; //probably don't want to fail outright..
			}
		}
	}

	return true;
}

Song Songregator::createSong(const Tag* tag, const FilePath& filePath)
{
	return Song(
		tag->track(),
		tag->title().toWString(),
		tag->artist().toWString(),
		tag->album().toWString(),
		filePath
	);
}