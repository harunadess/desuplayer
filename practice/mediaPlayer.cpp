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

void MediaPlayer::addToAdHocQueue(const Song& song)
{
	m_adhocPlayback->addSongToList(song);
}

void MediaPlayer::addToAdHocQueue(const Album& album)
{
	m_adhocPlayback->addContentsToList(album);
}

void MediaPlayer::addToAdHocQueue(const Artist& artist)
{
	m_adhocPlayback->addContentsToList(artist);
}

void MediaPlayer::addToAdHocQueue(const Playlist& playlist)
{
	m_adhocPlayback->addContentsToList(playlist);
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
		if (exitCode != 0)
		{
			if (exitCode == 1)
			{
				m_adhocPlayback->clear();
				m_playbackQueue->clear();
				m_ipc->writeToPipe(L"Cleared queue.");
				break;
			}
			else if (exitCode == 2)
			{
				m_ipc->writeToPipe(L"Skipping forward...");
				//continue;
			}
			else if (exitCode == 3)
			{
				m_ipc->writeToPipe(L"Skipping back...");
				playlist.getPrevious();
			}
		}
	}
}

void MediaPlayer::playQueued()
{
	m_ipc->writeToPipe(L"ESC - stop and clear queue.\nW/S adjust volume up/down.");

	if (m_playbackQueue->hasNext())
		playLoop(*m_playbackQueue);
	else
		m_ipc->writeToPipe(L"Queue empty");

	m_playbackQueue->clear();
}

void MediaPlayer::playImmediate()
{
	m_ipc->writeToPipe(L"ESC - stop and clear queue.\nW/S adjust volume up/down.");

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
