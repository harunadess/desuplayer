#ifndef ARTIST_H
#define ARTIST_H

#include <string>
using std::string;

class Artist
{
public:
	Artist(string name);
	~Artist();

	string getName();
	void setName(string name);

private:
	string name_;

};

#endif // !ARTIST_H
