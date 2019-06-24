#include "Artist.h"

Artist::Artist()
{
	name_ = L"";
	albumTitles_ = vector<wstring>();
	albums_ = map<wstring, vector<Song>>();
}

Artist::Artist(const wstring name)
{
	name_ = name;
	albumTitles_ = vector<wstring>();
	albums_ = map<wstring, vector<Song>>();
}

Artist::Artist(const wstring name, const map<wstring, vector<Song>> albums)
{
	name_ = name;
	albumTitles_ = vector<wstring>();
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
	albumTitles_.push_back(album);
	albums_[album].push_back(song);
}

vector<Song> Artist::getAlbum(const wstring& album) const
{
	try 
	{
		return albums_.at(album);
	}
	catch (const std::out_of_range e)
	{
		printf_s("%s: %s\n", "Couldn't find album ", e.what());
		return vector<Song>();
	}
}

vector<wstring> Artist::getAllAlbumTitles() const
{
	return albumTitles_;
}
