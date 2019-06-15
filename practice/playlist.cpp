#include "playlist.h"

Playlist::Playlist()
{
	title_ = "";
	songList_ = vector<Song>();
	index_ = 0;
}

Playlist::Playlist(const string& title)
{
	title_ = title;
	songList_ = vector<Song>();
	index_ = 0;
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

void Playlist::addAllToList_(vector<Song>& list)
{
	for (vector<Song>::iterator it = list.begin(); it != list.end(); ++it)
		addSongToList(*it);
}

void Playlist::addContentsToList(const Album& album)
{
	vector<Song> toAdd = album.getTrackList();
	addAllToList_(toAdd);
}

void Playlist::addContentsToList(const Artist& artist)
{
	map<wstring, vector<Song>> albums = artist.getAlbums();
	vector<wstring> albumTitles = artist.getAllAlbumTitles();

	for (vector<wstring>::iterator it = albumTitles.begin(); it != albumTitles.end(); ++it)
	{
		vector<Song> album = artist.getAlbum(*it);
		addAllToList_(album);
	}
}

void Playlist::addContentsToList(const Playlist& playlist)
{
	vector<Song> listContents = playlist.getSongList();
	addAllToList_(listContents);
}

bool Playlist::getNext(Song &song)
{
	if (index_ < songList_.size() - 1)
	{
		song = songList_.at(index_++);
		return true;
	}
	return false;
}

// todo: add "clear playlist" function
