#include "Song.h"

Song::Song(string title, Album* album, Artist* artist)
{
	this->title_ = title;
	this->album_ = new Album(*album);
	this->artist_ = new Artist(*artist);
}

Song::~Song()
{
	delete this->album_;
	delete this->artist_;
}

string Song::getTitle()
{
	return this->title_;
}

void Song::setTitle(string title)
{
	this->title_ = title;
}

Artist Song::getArtist()
{
	return *this->artist_;
}

void Song::setArtist(Artist* artist)
{
	this->artist_ = artist;
}

Album Song::getAlbum()
{
	return *this->album_;
}

void Song::setAlbum(Album* album)
{
	this->album_ = album;
}

const char* Song::getFilePath()
{
	return this->filePath_;
}

void Song::setFilePath(const char * filePath)
{
	this->filePath_ = filePath;
}
