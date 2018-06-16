#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Artist.h"
using std::string;

class Album
{
public:
	Album(string title, Artist* artist);
	~Album();

	string getTitle();
	void setTitle(string title);
	Artist getArtist();
	void setArtist(Artist* artist);

private:
	string title_;
	Artist* artist_;

};

#endif // !ALBUM_H
