#include "playlist.h"

Playlist::Playlist()
{
	title_ = "";
	songList_ = vector<Song>();
}

Playlist::Playlist(const string& title)
{
	title_ = title;
	songList_ = vector<Song>();
}

Playlist::~Playlist()
{
}

string Playlist::getTitle() const
{
	return title_;
}

void Playlist::setTitle(const string& title)
{
	title_ = title;
}

vector<Song> Playlist::getSongList() const
{
	return songList_;
}

void Playlist::setSongList(const vector<Song>& songList)
{
	songList_ = songList;
}

void Playlist::addSongToList(const Song& song)
{
	songList_.push_back(song);
}

void Playlist::addAlbumContentsToList(const Album& album)
{
	vector<Song> toAdd = album.getSelf();
	for (vector<Song>::iterator it = toAdd.begin(); it != toAdd.end(); ++it)
		songList_.push_back(*it);
}
