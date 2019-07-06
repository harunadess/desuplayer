#ifndef ALBUM_H
#define ALBUM_H

#include <vector>
#include <string>
#include "song.h"
#include "artist.h"

using std::vector;
using std::wstring;

class Album
{
public:
	Album();
	Album(const wstring& title, const wstring& artistName, vector<Song> trackList);
	~Album();

	wstring getTitle() const;
	void setTitle(const wstring& title);
	wstring getArtistName() const;
	void setArtistName(const wstring& artistName);
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
	wstring artistName_;
	vector<Song> trackList_;

};

#endif // !ALBUM_H
