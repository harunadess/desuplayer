#include "Album.h"

Album::Album(string title)
{
	this->title_ = title;
}

Album::~Album()
{
}

string Album::getTitle() 
{
	return this->title_;
}

void Album::setTitle(string title)
{
	this->title_ = title;
}