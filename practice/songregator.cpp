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

	FileRef fileRef;
	Tag* tag = nullptr;
	map<wstring, Artist> artistMap;
	map<wstring, Album> albumMap;
	map<wstring, Song> songMap;

	for (const FilePath& fp : filePaths)
	{
		fileRef = FileRef(fp.wideFilePath_.c_str());
		if (!fileRef.isNull() && fileRef.tag())
		{
			try
			{
				tag = fileRef.tag();
				wstring artistName = tag->artist().toWString();
				wstring normalisedArtistName = wstringToLower(artistName);

				if (artistNotInList(artistMap, normalisedArtistName))
					addArtistToList_(normalisedArtistName, artistMap);

				// artist add
				Song song = createSong_(tag, fp);
				addSongToArtist_(song, normalisedArtistName, artistMap);
				
				// song add
				std::pair<wstring, Song> songPair(song.getTitle(), song);
				songMap.insert(songMap.begin(), songPair);
			}
			catch (std::exception e)
			{
				std::wcerr << ("%s - (%d):", __FILE__, __LINE__) << e.what() << std::endl;
				//return false; // probably don't want to fail outright..
			}
		}
	}
	populateAlbumList_(albumMap, artistMap);
	
	musicLibrary.setArtists(artistMap);
	musicLibrary.setAlbums(albumMap);
	musicLibrary.setSongs(songMap);

	return true;
}

void Songregator::addArtistToList_(const wstring& artistName, map<wstring, Artist>& artistList)
{
	Artist artist(artistName);
	std::pair<wstring, Artist> insertPair(artistName, artist);
	artistList.insert(artistList.begin(), insertPair);
}

Song Songregator::createSong_(const Tag* tag, const FilePath& filePath)
{
	return Song(
		tag->track(),
		tag->title().toWString(),
		tag->artist().toWString(),
		tag->album().toWString(),
		filePath
	);
}

void Songregator::addSongToArtist_(Song& song, const wstring& artistName, map<wstring, Artist>& artistList)
{
	artistList[artistName].addSongToAlbum(song.getAlbum(), song);
}

void Songregator::populateAlbumList_(map<wstring, Album>& albumList, const map<wstring, Artist>& artistList)
{
	for (auto& artistPair : artistList)
	{
		Artist artist = artistPair.second;
		wstring artistName = artist.getName();
		map<wstring, vector<Song>> albums = artist.getAlbums();

		for (auto& albumPair : albums)
		{
			Album album(albumPair.first, artistName, albumPair.second);
			wstring albumKey = album.getTitle() + L"_" + album.getArtistName();	// <-- this line means albums are split by artist
			albumKey = wstringToLower(albumKey);							    // so compilations are split a bunch.							
																				
			std::pair<wstring, Album> insertPair(albumKey, album);	
			albumList.insert(insertPair);							
		}															
	}
	// before doing the insert into albumList I could maybe check if an entry already exists, if it does, then append with something else.
	// on the other hand, does having an album at a different map key make a huge difference?
	// depends on how well I code the search I guess.

	// i don't think the album key matters that much, if i make the search a bit better.
	// moderately defeats the purpose of the map structure, but changing that now is ehh
}
