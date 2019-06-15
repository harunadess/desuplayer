#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "player.h"
#include "song.h"
#include "artist.h"
#include "playlist.h"

class MediaPlayer : public Player
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

private:
	void playLoop_(Playlist &playlist);

	Playlist* playbackQueue_;
	Playlist* adhocPlayback_;
};

#endif // !MEDIAPLAYER_H