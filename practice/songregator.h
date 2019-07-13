#ifndef SONGREGATOR_H
#define SONGREGATOR_H

#include <map>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "artist.h"
#include "album.h"

class Songregator
{
public:
	Songregator();
	~Songregator();

	bool populateLibrary(std::wstring& baseDir, std::map<std::wstring, Artist>& artistMapOut, 
		std::map<std::wstring, Album>& albumMapOut, std::map<std::wstring, Song>& songMapOut);

private:
	void addArtistToList(const std::wstring& artistName, const std::wstring& normalisedArtistName, std::map<std::wstring, Artist>& artistList);
	Song createSong(const TagLib::Tag* tag, const FilePath& filePath);
	int populateSongAndArtistMaps(std::map<std::wstring, Song>& songMap, std::map<std::wstring, Artist>& artistMap, std::vector<FilePath> filePaths);
	int populateAlbumMap(std::map<std::wstring, Album>& albumMap, std::map<std::wstring, Song>& songMap);
	int populateArtistsWithAlbums(std::map<std::wstring, Artist>& artistMap, std::map<std::wstring, Album> albumMap);

};

#endif // !SONGREGATOR_H
