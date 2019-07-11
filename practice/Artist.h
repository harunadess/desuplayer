#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <map>
#include <vector>

#include "song.h"

class Artist
{
public:
	Artist();
	Artist(const std::wstring name);
	Artist(const std::wstring name, const std::map<std::wstring, std::vector<Song>> albumMap);
	~Artist();

	std::wstring getName() const;
	void setName(const std::wstring& name);
	std::map<std::wstring, std::vector<Song>> getAlbums() const;
	void setAlbumMap(const std::map<std::wstring, std::vector<Song>>& albumMap);
	void addSongToAlbum(const std::wstring& album, const Song& song);
	void addAlbumToList(const std::wstring albumKey, const std::wstring albumTitle , const std::vector<Song> albumTrackList);
	std::vector<Song> getAlbumName(const std::wstring& album) const;
	std::vector<std::wstring> getAllAlbumTitles() const;


	template<class Archive>
	void save(Archive& archive) const
	{
		archive(m_name, m_albumTitles, m_albumMap);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_name, m_albumTitles, m_albumMap);
	}

private:
	std::wstring m_name;
	std::vector<std::wstring> m_albumTitles;
	std::map<std::wstring, std::vector<Song>> m_albumMap;

};

#endif // !ARTIST_H
