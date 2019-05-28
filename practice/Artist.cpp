#include "Artist.h"

Artist::Artist()
{
	name_ = L"";
}

Artist::Artist(const wstring& name)
{
	name_ = name;
	albums_ = map<wstring, vector<Song>>();
}

Artist::Artist(const wstring& name, const map<wstring, vector<Song>>& albums)
{
	name_ = name;
	albums_ = albums;
}

Artist::~Artist()
{
}

wstring Artist::getName() const
{
	return name_;
}

void Artist::setName(const wstring& name)
{
	name_ = name;
}

map<wstring, vector<Song>> Artist::getAlbums() const
{
	return albums_;
}

void Artist::setAlbums(const map<wstring, vector<Song>>& albums)
{
	albums_ = albums;
}

void Artist::addSongToAlbum(const wstring& album, const Song& song)
{
	/*std::pair<wstring, Song> insertPair(album, song);*/
	/*albums_[album].insert(albums_[album].begin(), insertPair);*/
	albums_[album].push_back(song);
}

vector<Song> Artist::getAlbum(const wstring& album) const
{
	return albums_.at(album);
}