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

class MusicLibrary
{
public:
	MusicLibrary();
	~MusicLibrary();

	std::map<std::wstring, Artist> getArtistMap() const;
	void setArtistMap(const std::map<std::wstring, Artist>& artists);
	void setAlbumMap(const std::map<std::wstring, Album>& albums);
	void setSongMap(const std::map<std::wstring, Song>& songs);
	Artist getArtistName(const std::wstring& artistName) const;
	Album getAlbumName(const std::wstring& albumName) const;
	Song getSong(const std::wstring& songTitle) const;
	bool fullSearch(const std::wstring& searchTerms, SearchResults& searchResults) const;
	
	template<class Archive>
	void save(Archive& archive) const
	{
		archive(m_artists, m_albumMap, m_songMap, m_playlistList);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_artists, m_albumMap, m_songMap, m_playlistList);
	}

private:
	std::vector<Artist> searchArtists(const std::wstring& searchTerms) const;
	std::vector<Album> searchAlbums(const std::wstring& searchTerms) const;
	std::vector<Song> searchSongs(const std::wstring& searchTerms) const;

	std::map<std::wstring, Artist> m_artists;
	std::map<std::wstring, Album> m_albumMap;
	std::map<std::wstring, Song> m_songMap;
	std::vector<Playlist> m_playlistList;

};

#endif // !MUSICLIBRARY_H
