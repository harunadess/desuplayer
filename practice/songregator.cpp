#include "songregator.h"

using std::wstring;
using std::vector;
using std::map;

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

bool artistNotInList(const map<wstring, Artist>& artistList, const wstring& artist)
{
	for (auto& ap : artistList)
		if (ap.first.length() == artist.length() &&
			_wcsnicmp(ap.first.c_str(), artist.c_str(), ap.first.length()) == 0)
			return false;

	return true;
}


bool Songregator::populateLibrary(const wstring& baseDir, MusicLibrary& musicLibrary)
{
	vector<FilePath> filePaths = scanForMusicFiles(baseDir);

	if (filePaths.size() <= 0)
		return false;

	map<wstring, Song> songMap;
	map<wstring, Artist> artistMap;
	map<wstring, Album> albumMap;
	int error = populateSongAndArtistMaps(songMap, artistMap, filePaths);
	if (error == 0)
	{
		musicLibrary.setSongMap(songMap);
	}
	else
	{
		return false;
	}

	error = populateAlbumMap(albumMap, songMap);
	if (error == 0)
	{
		musicLibrary.setAlbumMap(albumMap);
	}
	else
	{
		return false;
	}

	error = populateArtistsWithAlbums(artistMap, albumMap);
	if (error == 0)
	{
		musicLibrary.setArtistMap(artistMap);
	}
	else
	{
		return false;
	}

	return true;
}

int Songregator::populateSongAndArtistMaps(map<wstring, Song>& songMap, map<wstring, Artist>& artistMap, vector<FilePath> filePaths)
{
	for (const FilePath& fp : filePaths)
	{
		TagLib::FileRef fileRef = TagLib::FileRef(fp.wideFilePath.c_str());
		if (!fileRef.isNull() && fileRef.tag())
		{
			try
			{
				TagLib::Tag* tag = fileRef.tag();
				wstring artistName = tag->artist().toWString();
				wstring normalisedArtistName = wstringToLower(artistName);

				// create artist with only name, other vars empty
				if (artistNotInList(artistMap, normalisedArtistName))
					addArtistToList(artistName, normalisedArtistName, artistMap);

				// create song, add to map
				// should use song map/list to populate albums/artists with song deets
				Song song = createSong(tag, fp);
				std::pair<wstring, Song> songPair(wstringToLower(song.getTitle()), song);
				songMap.insert(songMap.begin(), songPair);
			}
			catch (std::exception e)
			{
				std::wcerr << ("%s - (%d):", __FILE__, __LINE__) << e.what() << std::endl;
				//return 1; 
				// probably don't want to fail outright..
				// a lot of these are just tag bois
			}
		}
	}
	return 0;
}

void Songregator::addArtistToList(const wstring& artistName, const wstring& normalisedArtistName, map<wstring, Artist>& artistList)
{
	Artist artist(artistName);
	std::pair<wstring, Artist> insertPair(normalisedArtistName, artist);
	artistList.insert(artistList.begin(), insertPair);
}

Song Songregator::createSong(const TagLib::Tag* tag, const FilePath& filePath)
{
	return Song(
		tag->track(),
		tag->title().toWString(),
		tag->artist().toWString(),
		tag->album().toWString(),
		filePath
	);
}

int Songregator::populateAlbumMap(map<wstring, Album>& albumMap, map<wstring, Song>& songMap)
{
	for (auto& sp : songMap)
	{
		Song s = sp.second;
		bool found = false;

		// check if song's album exists
		// if it does, add it to it
		// else, create new album, add song to it
		for (auto it = albumMap.begin(); it != albumMap.end(); ++it)
		{
			wstring itAlbumTitle = wstringToLower(it->second.getTitle());
			wstring itArtist = wstringToLower(it->second.getArtistName());
			wstring sAlbumTitle = wstringToLower(s.getAlbumTitle());
			wstring sArtist = wstringToLower(s.getArtistName());

			found = (itArtist.compare(sArtist) == 0 && itAlbumTitle.compare(sAlbumTitle) == 0);

			if (found)
				break;
		}

		wstring sAlbumKey = wstringToLower(s.getAlbumTitle());
		if (!found)
		{
			std::pair<wstring, Album> ap(sAlbumKey, Album(s.getAlbumTitle(), s.getArtistName()));
			albumMap.insert(ap);
		}
		albumMap.at(sAlbumKey).setTrackAt(s.getTrackNumber(), s);
	}

	return 0;
}

int Songregator::populateArtistsWithAlbums(map<wstring, Artist>& artistMap, map<wstring, Album> albumMap)
{
	for (auto& ap : albumMap)
	{
		Album a = ap.second;

		wstring artistKey = wstringToLower(a.getArtistName());
		wstring albumKey = wstringToLower(a.getTitle());

		artistMap.at(artistKey).addAlbumToList(albumKey, a.getTitle(), a.getTrackList());
	}

	return 0;
}
