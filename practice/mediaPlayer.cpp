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
	vector<wstring> albumNames;
	//todo: move this album names vector to the artist class
	for (map<wstring, vector<Song>>::iterator it = albums.begin(); it != albums.end(); ++it)
	{
		albumNames.push_back(it->first);
	}

	for (vector<wstring>::iterator it = albumNames.begin(); it != albumNames.end(); ++it)
	{

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
