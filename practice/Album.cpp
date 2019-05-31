#include "album.h"

Album::Album()
{
	title_ = L"";
	trackList_ = vector<Song>();
}

Album::Album(const wstring& title, vector<Song> trackList)
{
	title_ = title;
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

//Artist* Album::getArtist() const
//{
//	return artist_;
//}

wstring Album::getArtistName() const
{
	return trackList_.at(0).getArtist();
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