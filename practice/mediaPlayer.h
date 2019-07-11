#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "player.h"
#include "song.h"
#include "artist.h"
#include "playlist.h"

class MediaPlayer 
	: public Player
{
public:
	MediaPlayer();
	~MediaPlayer();

	void addToPlaybackQueue(const Song& song);
	void addToPlaybackQueue(const Album& album);
	void addToPlaybackQueue(const Artist& artist);
	void addToPlaybackQueue(const Playlist& playlist);
	void playImmediately(const Song& song);
	void playImmediately(const Album& album);
	void playImmediately(const Artist &artist);
	void playImmediately(const Playlist &playlist);
	void playQueued();

private:
	void playLoop(Playlist &playlist);

	Playlist* m_playbackQueue;
	Playlist* m_adhocPlayback;
};

#endif // !MEDIAPLAYER_H
