#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <map>
#include <vector>
#include <string>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include "artist.h"
#include "playlist.h"

using std::wstring;
using std::map;
using std::vector;

class MusicLibrary
{
public:
	MusicLibrary();
	~MusicLibrary();

	map<wstring, Artist> getArtists() const;
	void setArtists(const map<wstring, Artist>& artists);
	Artist getArtist(const wstring& artistName) const;

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(artists_, playlists_);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(artists_, playlists_);
	}

private:
	map<wstring, Artist> artists_;
	vector<Playlist> playlists_;

};

#endif // !MUSICLIBRARY_H
