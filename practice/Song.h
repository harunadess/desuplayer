#ifndef SONG_H
#define SONG_H

#include <string>
#include "Artist.h"
#include "Album.h"
using std::string;

class Song
{
public:
	Song(string title, Album* album, Artist* artist);
	~Song();

	string getTitle();
	void setTitle(string title);
	Artist getArtist();
	void setArtist(Artist* artist);
	Album getAlbum();
	void setAlbum(Album* album);

	const char* getFilePath();
	void setFilePath(const char* filePath);

private:
	string title_;
	Artist* artist_;
	Album* album_;
	const char* filePath_;

};

#endif // !SONG_H
