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
		//todo: use m_io
		std::wcout << L"Now playing: " << current.getTitle() << L" - " << current.getArtistName() << std::endl;
		int exitCode = play(current.getFilePath().u8FilePath);
		if (exitCode != 0)
		{
			if (exitCode == 1)
			{
				m_adhocPlayback->clear();
				m_playbackQueue->clear();
				std::wcout << std::endl << "Cleared queue." << std::endl;
				break;
			}

			if (exitCode == 2)
			{
				std::wcout << L"Skipping forward..." << std::endl;
				continue;
			}

			if (exitCode == 3)
			{
				std::wcout << L"Skipping back..." << std::endl;
				playlist.getPrevious();
			}
		}
	}
}

void MediaPlayer::playQueued()
{
	std::wcout << L"Use <F3> to Pause/Play. Use <F2>/<F4> to skip back/forward. Use ESC to stop and clear the queue." << std::endl;

	if (m_playbackQueue->hasNext())
		playLoop(*m_playbackQueue);
	else
		std::wcout << L"Queue empty" << std::endl;

	m_playbackQueue->clear();
}

void MediaPlayer::playImmediate()
{
	std::wcout << L"Use <F3> to Pause/Play. Use <F2>/<F4> to skip back/forward. Use ESC to stop and clear the queue." << std::endl;


	if (m_adhocPlayback->hasNext())
		playLoop(*m_adhocPlayback);
	else
		std::wcout << L"No item to play" << std::endl;

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
