#include "songregator.h"

#include "musicFileFinder.h"
#include "util.h"

using std::wstring;
using std::vector;
using std::map;

Songregator::Songregator()
{
}

Songregator::~Songregator()
{
}

bool artistNotInList(const map<wstring, Artist>& artistList, const wstring& artist)
{
	for (auto& ap : artistList)
		if (ap.first.length() == artist.length() &&
			_wcsnicmp(ap.first.c_str(), artist.c_str(), ap.first.length()) == 0)
			return false;

	return true;
}

bool Songregator::populateLibrary(wstring& baseDir, std::map<std::wstring, Artist>& artistMapOut, 
	std::map<std::wstring, Album>& albumMapOut, std::map<std::wstring, Song>& songMapOut)
{
	MusicFileFinder finder;
	vector<FilePath> filePaths = finder.scanForNewFiles(baseDir);

	if (filePaths.size() <= 0)
		return false;
	std::wcout << L"Validated" << std::endl;

	std::wcout << L"Files found: " << filePaths.size() << std::endl;
	
	std::wcout << "Building library..." << std::endl;
	map<wstring, Song> songMap;
	map<wstring, Artist> artistMap;
	map<wstring, Album> albumMap;

	std::wcout << L"Building song data..." << std::endl;
	int error = populateSongAndArtistMaps(songMap, artistMap, filePaths);
	
	if (error == 0)
		songMapOut = songMap;
	else
		return false;

	std::wcout << L"Buidling album data..." << std::flush;
	error = populateAlbumMap(albumMap, songMap);
	
	if (error == 0)
		albumMapOut = albumMap;
	else
		return false;
	std::wcout << L" Done" << std::endl;

	std::wcout << L"Building artist data..." << std::flush;
	error = populateArtistsWithAlbums(artistMap, albumMap);

	if (error == 0)
		artistMapOut = artistMap;
	else
		return false;
	std::wcout << L" Done" << std::endl;

	std::wcout << L"Building library... Done" << std::endl;

	return true;
}

int Songregator::populateSongAndArtistMaps(map<wstring, Song>& songMap, map<wstring, Artist>& artistMap, vector<FilePath> filePaths)
{
	int pathIndex = 0;
	int milestonesIndex = 0;
	size_t milestones[11] = { 0 };
	size_t tenth = filePaths.size() / 10;

	for (int i = 1; i <= 10; i++)
		milestones[i] = tenth * i;

	for (const FilePath& fp : filePaths)
	{
		++pathIndex;
		if (pathIndex >= milestones[milestonesIndex])
		{
			std::wcout << (milestonesIndex * 10) << L"%..\n" << std::flush;
			++milestonesIndex;
		}

		TagLib::FileRef fileRef = TagLib::FileRef(fp.wideFilePath.c_str());
		if (!fileRef.isNull() && fileRef.tag())
		{
			try
			{
				TagLib::Tag* tag = fileRef.tag();
				TagLib::AudioProperties* audioProps = fileRef.audioProperties();

				wstring artistName = tag->artist().toWString();
				if (artistName.find(L"Ayame") != wstring::npos)
					std::wcout << "here";
				wstring normalisedArtistName = wstringToLower(artistName);

				// create artist with only name, other vars empty
				if (artistNotInList(artistMap, normalisedArtistName))
					addArtistToList(artistName, normalisedArtistName, artistMap);

				// create song, add to map
				Song song = createSong(tag, audioProps, fp);
				std::pair<wstring, Song> songPair((wstringToLower(song.getTitle() + L"_" + song.getAlbumTitle())), song);
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
	std::wcout << std::endl << "Building song data... Done" << std::endl;

	return 0;
}

void Songregator::addArtistToList(const wstring& artistName, const wstring& normalisedArtistName, map<wstring, Artist>& artistList)
{
	Artist artist(artistName);
	std::pair<wstring, Artist> insertPair(normalisedArtistName, artist);
	artistList.insert(artistList.begin(), insertPair);
}

Song Songregator::createSong(const TagLib::Tag* tag, const TagLib::AudioProperties* audioProperties, const FilePath& filePath)
{
	const AudioProperties ap(audioProperties->bitrate(), audioProperties->channels(), audioProperties->lengthInSeconds(),
		audioProperties->lengthInMilliseconds(), audioProperties->sampleRate());

	return Song(tag->track(), tag->title().toWString(), tag->artist().toWString(), 
		tag->album().toWString(), tag->genre().toWString(), ap, filePath);
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

		albumMap.at(sAlbumKey).addTrack(s);
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
