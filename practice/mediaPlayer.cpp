#include "mediaPlayer.h"

MediaPlayer::MediaPlayer()
{
	playbackQueue_ = new Playlist();
	adhocPlayback_ = new Playlist();
}

MediaPlayer::~MediaPlayer()
{
	delete playbackQueue_;
	delete adhocPlayback_;
}

void MediaPlayer::addToPlaybackQueue(const Song& song)
{
	playbackQueue_->addSongToList(song);
}

void MediaPlayer::addToPlaybackQueue(const Album& album)
{
	playbackQueue_->addContentsToList(album);
}

void MediaPlayer::addToPlaybackQueue(const Artist& artist)
{
	playbackQueue_->addContentsToList(artist);
}

void MediaPlayer::addToPlaybackQueue(const Playlist& playlist)
{
	playbackQueue_->addContentsToList(playlist);
}

void MediaPlayer::playImmediately(const Song& song)
{
	adhocPlayback_->addSongToList(song);
	playLoop_(*adhocPlayback_);
}

void MediaPlayer::playImmediately(const Album& album)
{
	adhocPlayback_->addContentsToList(album);
	playLoop_(*adhocPlayback_);
}

void MediaPlayer::playImmediately(const Artist& artist)
{
	adhocPlayback_->addContentsToList(artist);
	playLoop_(*adhocPlayback_);
}

void MediaPlayer::playImmediately(const Playlist& playlist)
{
	adhocPlayback_->addContentsToList(playlist);
	playLoop_(*adhocPlayback_);
}

void MediaPlayer::playLoop_(Playlist &playlist)
{
	Song current;
	while (playlist.getNext(current))
	{
		wcout << "Now playing: " << current.getTitle() << " - " << current.getArtist() << endl;
		play(current.getFilePath().u8FilePath_);
	}
}
