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
