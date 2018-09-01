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

	//bool createSongList(const wstring& baseDirectory, vector<Song>& songList);
	//bool createSongList(const wstring& baseDirectory, map<wstring, Artist>& artistList);
	bool createSongList(const wstring& baseDirectory, MusicLibrary& musicLibrary);

private:
	Song createSong(const Tag* tag, const FilePath& filePath);
	void addSongToArtist(const Tag* tag, const wstring& artistName, map<wstring, Artist>& artistList, const FilePath& filePath);
};

#endif // !SONGREGATOR_H
