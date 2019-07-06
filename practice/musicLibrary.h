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
#include "Album.h"
#include "Song.h"
#include "searchResults.h"
#include "util.h"

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
	void setAlbums(const map<wstring, Album>& albums);
	void setSongs(const map<wstring, Song>& songs);

	Artist getArtist(const wstring& artistName) const;	// todo: fix these methods, as they require "exact" typings
	Album getAlbum(const wstring& albumName) const;
	Song getSong(const wstring& songTitle) const;

	bool unifiedSearch(const wstring& searchTerms, SearchResults& searchResults) const;
	
	template<class Archive>
	void save(Archive& archive) const
	{
		archive(artists_, albums_, songs_, playlists_);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(artists_, albums_, songs_, playlists_);
	}

private:
	map<wstring, Artist> artists_;
	map<wstring, Album> albums_;
	map<wstring, Song> songs_;
	vector<Playlist> playlists_;

	vector<Artist> searchArtists_(const wstring& searchTerms) const;
	vector<Album> searchAlbums_(const wstring& searchTerms) const;
	vector<Song> searchSongs_(const wstring& searchTerms) const;

};





#endif // !MUSICLIBRARY_H
