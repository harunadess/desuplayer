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
	MediaPlayer(MpControls& mpControls, IPC* ipc);
	~MediaPlayer();

	//todo: convert these to return an int/size_t of how many items were queued.
	size_t addToPlaybackQueue(const Song& song);
	size_t addToPlaybackQueue(const Album& album);
	size_t addToPlaybackQueue(const Artist& artist);
	size_t addToPlaybackQueue(const Playlist& playlist);
	size_t addToAdHocQueue(const Song& song);
	size_t addToAdHocQueue(const Album& album);
	size_t addToAdHocQueue(const Artist& artist);
	size_t addToAdHocQueue(const Playlist& playlist);
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
