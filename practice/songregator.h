#ifndef SONGREGATOR_H
#define SONGREGATOR_H

#include <map>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "musicFileFinder.h"
#include "artist.h"
#include "musicLibrary.h"

using std::map;
using std::wstring;
using TagLib::FileRef;
using TagLib::Tag;

class Songregator
{
public:
	Songregator();
	~Songregator();

	bool populateLibrary(const wstring& baseDirectory, MusicLibrary& musicLibrary);

private:
	void addArtistToList_(const wstring& ArtistName, map<wstring, Artist>& artistList);
	Song createSong_(const Tag* tag, const FilePath& filePath);
	void addSongToArtist_(Song& song, const wstring& artistName, map<wstring, Artist>& artistList);
	void populateAlbumList_(map<wstring, Album>& albumList, const map<wstring, Artist>& artistList);

};

#endif // !SONGREGATOR_H
