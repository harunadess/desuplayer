#include "mediaPlayer.h"

MediaPlayer::MediaPlayer()
{
	m_playbackQueue = new Playlist(L"playback queue");
	m_adhocPlayback = new Playlist(L"adhoc playback queue");
}

MediaPlayer::~MediaPlayer()
{
	delete m_playbackQueue;
	delete m_adhocPlayback;
}

void MediaPlayer::addToPlaybackQueue(const Song& song)
{
	m_playbackQueue->addSongToList(song);
}

void MediaPlayer::addToPlaybackQueue(const Album& album)
{
	m_playbackQueue->addContentsToList(album);
}

void MediaPlayer::addToPlaybackQueue(const Artist& artist)
{
	m_playbackQueue->addContentsToList(artist);
}

void MediaPlayer::addToPlaybackQueue(const Playlist& playlist)
{
	m_playbackQueue->addContentsToList(playlist);
}

void MediaPlayer::playImmediately(const Song& song)
{
	m_adhocPlayback->addSongToList(song);
	playLoop(*m_adhocPlayback);
}

void MediaPlayer::playImmediately(const Album& album)
{
	m_adhocPlayback->addContentsToList(album);
	playLoop(*m_adhocPlayback);
}

void MediaPlayer::playImmediately(const Artist& artist)
{
	m_adhocPlayback->addContentsToList(artist);
	playLoop(*m_adhocPlayback);
}

void MediaPlayer::playImmediately(const Playlist& playlist)
{
	m_adhocPlayback->addContentsToList(playlist);
	playLoop(*m_adhocPlayback);
}

void MediaPlayer::playLoop(Playlist &playlist)
{
	Song current;
	while (playlist.getNext(current))
	{
		//todo: use m_io
		std::wcout << "Now playing: " << current.getTitle() << " - " << current.getArtistName() << std::endl;
		play(current.getFilePath().u8FilePath);
	}
}

void MediaPlayer::playQueued()
{
	Song current;
	if (m_adhocPlayback->getNext(current))
	{
		playLoop(*m_adhocPlayback);
	}

	if (m_playbackQueue->getNext(current))
	{
		playLoop(*m_playbackQueue);
	}
}
