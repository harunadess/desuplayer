#include "Artist.h"

Artist::Artist(std::string name)
{
	this->name_ = name;
}

Artist::~Artist()
{
}

std::string Artist::getName()
{
	return this->name_;
}

void Artist::setName(std::string name)
{
	this->name_ = name;
}
