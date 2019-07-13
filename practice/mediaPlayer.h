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
	void addToAdHocQueue(const Song& song);
	void addToAdHocQueue(const Album& album);
	void addToAdHocQueue(const Artist& artist);
	void addToAdHocQueue(const Playlist& playlist);
	Playlist* getPlaybackQueue();
	Playlist* getAdhocPlayback();
	void playImmediate();
	void playQueued();

private:
	void playLoop(Playlist &playlist);

	Playlist* m_playbackQueue;
	Playlist* m_adhocPlayback;
};

#endif // !MEDIAPLAYER_H
