#ifndef ARTIST_H
#define ARTIST_H

#include <string>
using std::string;

class Artist
{
public:
	Artist(std::string name);
	~Artist();

	std::string getName();
	void setName(std::string name);

private:
	std::string name_;

};

#endif // !ARTIST_H
