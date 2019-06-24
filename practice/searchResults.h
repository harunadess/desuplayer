#ifndef SEARCH_RESULTS_H
#define SEARCH_RESULTS_H

#include "album.h"
#include "Artist.h"
#include "Song.h"

using std::vector;

class SearchResults
{
public:
	vector<Album> albums;
	vector<Artist> artists;
	vector<Song> songs;

private:
	
};

#endif // !SEARCH_RESULTS_H
