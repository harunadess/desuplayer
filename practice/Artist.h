#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <vector>
#include "Album.h"

class Album;

using std::vector;
using std::wstring;

class Artist
{
public:
	Artist();
	Artist(const wstring& name);
	Artist(const wstring& name, const vector<Album*>& albums);
	~Artist();

	wstring getName() const;
	void setName(const wstring& name);
	vector<Album*> getAlbums() const;
	void setAlbums(const vector<Album*>& albums);
	void addAlbum(Album* album);
	void removeAlbum(const wstring& name);

private:
	wstring name_;
	vector<Album*> albums_;

};

#endif // !ARTIST_H
