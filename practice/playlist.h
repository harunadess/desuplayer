#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <string>
#include "song.h"
#include "album.h"

using std::vector;
using std::string;

class Playlist
{
public:
	Playlist();
	Playlist(const string& title);
	~Playlist();

	string getTitle() const;
	void setTitle(const string& title);

	vector<Song> getSongList() const;
	void setSongList(const vector<Song>& songList);

	void addSongToList(const Song& song);
	void addContentsToList(const Album& album);
	void addContentsToList(const Artist& album);
	void addContentsToList(const Playlist& album);

	bool getNext(Song &song);

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(title_, songList_);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(title_, songList_);
	}

private:
	void addAllToList_(vector<Song>& list);

	string title_;
	vector<Song> songList_;
	unsigned int index_;
};

#endif // !PLAYLIST_H
