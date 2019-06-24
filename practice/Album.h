#ifndef ALBUM_H
#define ALBUM_H

#include <vector>
#include <string>
#include "song.h"
#include "artist.h"

using std::vector;
using std::wstring;

//class Artist;  <-- unsure of use, probably compilation stuff

class Album
{
public:
	Album();
	Album(const wstring& title, vector<Song> trackList);
	~Album();

	wstring getTitle() const;
	void setTitle(const wstring& title);
	//Artist* getArtist() const;
	wstring getArtistName() const;
	vector<Song> getTrackList() const;
	Song getTrackAt(int pos) const;

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(title_, trackList_);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(title_, trackList_);
	}

private:
	wstring title_;
	vector<Song> trackList_;

};

#endif // !ALBUM_H
