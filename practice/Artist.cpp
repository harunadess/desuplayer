#include "Artist.h"

Artist::Artist()
{
	name_ = L"";
	albums_ = vector<Album*>();
}

Artist::Artist(const wstring& name)
{
	name_ = name;
}

Artist::Artist(const wstring& name, const vector<Album*>& albums)
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

vector<Album*> Artist::getAlbums() const
{
	return albums_;
}

void Artist::setAlbums(const vector<Album*>& albums)
{
	albums_ = albums;
}

void Artist::addAlbum(Album* album)
{
	albums_.push_back(album);
}

void Artist::removeAlbum(const wstring& name)
{
	//todo: find album with name, remove from list
}
