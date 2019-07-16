#ifndef SEARCH_RESULTS_H
#define SEARCH_RESULTS_H

#include "album.h"
#include "Artist.h"
#include "Song.h"

class SearchResults
{
public:
	std::vector<Album> albums;
	std::vector<Artist> artists;
	std::vector<Song> songs;
	std::vector<Playlist> playlists;

};

#endif // !SEARCH_RESULTS_H
