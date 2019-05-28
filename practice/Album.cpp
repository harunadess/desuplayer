#include "album.h"

Album::Album()
{
	title_ = L"";
	artist_ = nullptr;
}

Album::Album(const wstring& title, Artist* artist)
{
	title_ = title;
	artist_ = artist;
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

Artist* Album::getArtist() const
{
	return artist_;
}

void Album::setArtist(Artist* artist)
{
	artist_ = artist;
}

wstring Album::getArtistName() const
{
	return L"";
}

vector<Song> Album::getSelf() const
{
	return artist_->getAlbum(title_);
}
