#include "album.h"

Album::Album()
{
	title_ = L"";
	artistName_ = L"";
	trackList_ = vector<Song>();
}

Album::Album(const wstring& title, const wstring& artistName, vector<Song> trackList)
{
	title_ = title;
	artistName_ = artistName;
	trackList_ = trackList;
}

Album::~Album()
{
}

wstring Album::getTitle() const
{
	return title_;
}

void Album::setTitle(const wstring& title)
{
	title_ = title;
}

wstring Album::getArtistName() const
{
	return artistName_;
}

void Album::setArtistName(const wstring& artistName)
{
	artistName_ = artistName;
}

vector<Song> Album::getTrackList() const
{
	return trackList_;
}

Song Album::getTrackAt(int pos) const
{
	if (pos < 0 || pos > trackList_.size() - 1)
		return Song();

	return trackList_.at(pos);
}