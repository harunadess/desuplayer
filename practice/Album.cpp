#include "Album.h"

Album::Album(string title, Artist* artist)
{
	this->title_ = title;
	this->artist_ = artist;
}

Album::~Album()
{
	delete this->artist_;
}

string Album::getTitle() 
{
	return this->title_;
}

void Album::setTitle(string title)
{
	this->title_ = title;
}

Artist Album::getArtist()
{
	return *this->artist_;
}

void Album::setArtist(Artist* artist)
{
	this->artist_ = artist;
}
