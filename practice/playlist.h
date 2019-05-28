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
	void addAlbumContentsToList(const Album& album);

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
	string title_;
	vector<Song> songList_;

};

#endif // !PLAYLIST_H
