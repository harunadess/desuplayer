#ifndef SONGREGATOR_H
#define SONGREGATOR_H

#include <vector>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "song.h"
#include "musicFileFinder.h"

using std::vector;
using TagLib::FileRef;
using TagLib::Tag;

class Songregator
{
public:
	Songregator();
	~Songregator();

	bool createSongList(const wstring& baseDirectory, vector<Song>& songList);

private:
	Song createSong(const Tag* tag, const FilePath& filePath);
};

#endif // !SONGREGATOR_H
