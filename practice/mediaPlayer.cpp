#include "mediaPlayer.h"

MediaPlayer::MediaPlayer(MpControls& mpControls, IPC* ipc) 
	: Player(mpControls, ipc)
{
	m_playbackQueue = new Playlist(L"playback queue");
	m_adhocPlayback = new Playlist(L"adhoc playback queue");
}

MediaPlayer::~MediaPlayer()
{
	delete m_playbackQueue;
	delete m_adhocPlayback;
}

size_t MediaPlayer::addToPlaybackQueue(const Song& song)
{
	const size_t sizeBefore = m_playbackQueue->getSongList().size();
	m_playbackQueue->addSongToList(song);
	const size_t sizeAfter = m_playbackQueue->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToPlaybackQueue(const Album& album)
{
	const size_t sizeBefore = m_playbackQueue->getSongList().size();
	m_playbackQueue->addContentsToList(album);
	const size_t sizeAfter = m_playbackQueue->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToPlaybackQueue(const Artist& artist)
{
	const size_t sizeBefore = m_playbackQueue->getSongList().size();
	m_playbackQueue->addContentsToList(artist);
	const size_t sizeAfter = m_playbackQueue->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToPlaybackQueue(const Playlist& playlist)
{
	const size_t sizeBefore = m_playbackQueue->getSongList().size();
	m_playbackQueue->addContentsToList(playlist);
	const size_t sizeAfter = m_playbackQueue->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToAdHocQueue(const Song& song)
{
	const size_t sizeBefore = m_adhocPlayback->getSongList().size();
	m_adhocPlayback->addSongToList(song);
	const size_t sizeAfter = m_adhocPlayback->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToAdHocQueue(const Album& album)
{
	const size_t sizeBefore = m_adhocPlayback->getSongList().size();
	m_adhocPlayback->addContentsToList(album);
	const size_t sizeAfter = m_adhocPlayback->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToAdHocQueue(const Artist& artist)
{
	const size_t sizeBefore = m_adhocPlayback->getSongList().size();
	m_adhocPlayback->addContentsToList(artist);
	const size_t sizeAfter = m_adhocPlayback->getSongList().size();

	return sizeAfter - sizeBefore;
}

size_t MediaPlayer::addToAdHocQueue(const Playlist& playlist)
{
	const size_t sizeBefore = m_adhocPlayback->getSongList().size();
	m_adhocPlayback->addContentsToList(playlist);
	const size_t sizeAfter = m_adhocPlayback->getSongList().size();

	return sizeAfter - sizeBefore;
}

void MediaPlayer::playLoop(Playlist &playlist)
{
	Song current;
	while (playlist.getNext(current))
	{
		m_ipc->writeToPipe((L"Now playing: " + current.getTitle() + L" - " + current.getArtistName()));

		PlayDeets playDeets;
		playDeets.filePath = current.getFilePath().u8FilePath;
		play(playDeets);

		int exitCode = playDeets.exitCode;
		if (exitCode != NORMAL)
		{
			if (exitCode == EXIT)
			{
				m_adhocPlayback->clear();
				m_playbackQueue->clear();
				m_ipc->writeToPipe(L"Stopped, and cleared queue.");
				break;
			}
			else if (exitCode == NEXT)
			{
				m_ipc->writeToPipe(L"Skipping forward...");
			}
			else if (exitCode == PREVIOUS)
			{
				m_ipc->writeToPipe(L"Skipping back...");
				playlist.getPrevious();
			}
			else if (exitCode == STOP)
			{
				m_ipc->writeToPipe(L"Stopping playback...");
			}
		}
	}
}

void MediaPlayer::playQueued()
{
	m_ipc->writeToPipe(L"ESC - stop and clear queue.\n");

	if (m_playbackQueue->hasNext())
		playLoop(*m_playbackQueue);
	else
		m_ipc->writeToPipe(L"Queue empty");

	m_playbackQueue->clear();
}

void MediaPlayer::playImmediate()
{
	m_ipc->writeToPipe(L"ESC - stop and clear queue.\n.");

	if (m_adhocPlayback->hasNext())
		playLoop(*m_adhocPlayback);
	else
		m_ipc->writeToPipe(L"No item to play");

	m_adhocPlayback->clear();
}

Playlist* MediaPlayer::getPlaybackQueue()
{
	return m_playbackQueue;
}

Playlist* MediaPlayer::getAdhocPlayback()
{
	return m_adhocPlayback;
}
