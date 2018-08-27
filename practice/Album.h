#ifndef ALBUM_H
#define ALBUM_H

#include <vector>
#include <string>

using std::vector;
using std::wstring;

class Artist;

class Album
{
public:
	Album();
	Album(const wstring& title, Artist* artist);
	~Album();

	wstring getTitle() const;
	void setTitle(const wstring& title);
	Artist* getArtist() const;
	void setArtist(Artist* aritst);
	wstring getArtistName() const;

private:
	wstring title_;
	Artist* artist_;

};

#endif // !ALBUM_H
