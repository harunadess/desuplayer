#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <vector>
#include "Artist.h"
#include "Playlist.h"

using std::vector;

class MusicLibrary
{
public:
	MusicLibrary();
	~MusicLibrary();

private:
	vector<Artist> artists_;
	vector<Playlist> playlists_;

};

#endif // !MUSICLIBRARY_H
