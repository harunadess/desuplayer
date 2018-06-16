#include "Artist.h"

Artist::Artist(string name)
{
	this->name_ = name;
}

Artist::~Artist()
{
}

string Artist::getName()
{
	return this->name_;
}

void Artist::setName(string name)
{
	this->name_ = name;
}
