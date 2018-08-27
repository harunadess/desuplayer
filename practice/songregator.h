#ifndef SONGREGATOR_H
#define SONGREGATOR_H

//#include <vector>
#include <map>
#include <taglib/fileref.h>
#include <taglib/tag.h>
//#include "song.h"
#include "musicFileFinder.h"
#include "artist.h"

using std::map;
using TagLib::FileRef;
using TagLib::Tag;

class Songregator
{
public:
	Songregator();
	~Songregator();

	//bool createSongList(const wstring& baseDirectory, vector<Song>& songList);
	bool createSongList(const wstring& baseDirectory, map<wstring, Artist>& artistList);

private:
	Song createSong(const Tag* tag, const FilePath& filePath);
	void addSongToArtist(const Tag* tag, const wstring& artistName, map<wstring, Artist>& artistList, const FilePath& filePath);
};

#endif // !SONGREGATOR_H
