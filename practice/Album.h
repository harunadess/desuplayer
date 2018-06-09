#ifndef ALBUM_H
#define ALBUM_H

#include <string>
using std::string;

class Album
{
public:
	Album(string title);
	~Album();

	string getTitle();
	void setTitle(string title);

private:
	string title_;

};

#endif // !ALBUM_H
