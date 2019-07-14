#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <string>

#include "song.h"
#include "album.h"

class Playlist
{
public:
	Playlist();
	Playlist(const std::wstring& title);
	~Playlist();

	std::wstring getTitle() const;
	void setTitle(const std::wstring& title);
	std::vector<Song> getSongList() const;
	void setSongList(const std::vector<Song>& songList);
	void addSongToList(const Song& song);
	void addContentsToList(const Album& album);
	void addContentsToList(const Artist& album);
	void addContentsToList(const Playlist& album);
	bool getNext(Song &song);
	bool hasNext();
	bool getPrevious();
	void clear();

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(m_title, m_songList);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_title, m_songList);
	}

private:
	void addAllToList(std::vector<Song>& list);

	std::wstring m_title;
	std::vector<Song> m_songList;
	unsigned int m_listIndex;
};

#endif // !PLAYLIST_H
