#ifndef ALBUM_H
#define ALBUM_H

#include <vector>
#include <string>

#include "song.h"
#include "artist.h"

class Album
{
public:
	Album();
	Album(const std::wstring& title, const std::wstring& artistName, std::vector<Song> trackList);
	Album(const std::wstring& title, const std::wstring& artistName);
	~Album();

	std::wstring getTitle() const;
	void setTitle(const std::wstring& title);
	std::wstring getArtistName() const;
	void setArtistName(const std::wstring& artistName);
	std::vector<Song> getTrackList() const;
	void setTrackAt(int pos, Song song);
	Song getTrackAt(int pos) const;

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(m_title, m_artistName, m_trackList);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_title, m_artistName, m_trackList);
	}

private:
	std::wstring m_title;
	std::wstring m_artistName;
	std::vector<Song> m_trackList;

};

#endif // !ALBUM_H
