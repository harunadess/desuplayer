#include "mediaPlayer.h"

MediaPlayer::MediaPlayer()
{
	playbackQueue_ = new Playlist();
}

MediaPlayer::~MediaPlayer()
{
	delete playbackQueue_;
}

void MediaPlayer::addToPlaybackQueue(const Song& song)
{
	playbackQueue_->addSongToList(song);
}

void MediaPlayer::addToPlaybackQueue(const Album& album)
{
	playbackQueue_->addAlbumContentsToList(album);
}

void MediaPlayer::addToPlaybackQueue(const Artist& artist)
{
	map<wstring, vector<Song>> albums = artist.getAlbums();
	vector<wstring> albumTitles = artist.getAllAlbumTitles();
	
	for (vector<wstring>::iterator it = albumTitles.begin(); it != albumTitles.end(); ++it)
	{
		vector<Song> album = artist.getAlbum(*it);
		for (vector<Song>::iterator songIt = album.begin(); songIt != album.end(); ++songIt)
			playbackQueue_->addSongToList(*songIt);
	}
}

void MediaPlayer::addToPlaybackQueue(const Playlist& playlist)
{

}

void MediaPlayer::playImmediately(const Song& song)
{

}

void MediaPlayer::playImmediately(const Album& album)
{

}

void MediaPlayer::playImmediately(const Artist& artist)
{

}

void MediaPlayer::playImmediately(const Playlist& playlist)
{

}
