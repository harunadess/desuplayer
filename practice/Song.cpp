#include "song.h"

Song::Song()
{
	trackNumber_ = 0;
	title_ = L"";
	artist_ = L"";
	album_ = L"";
	//filePath_ = FilePath();
}

Song::Song(const unsigned int& trackNumber, const wstring& title, const wstring& artist, const wstring& album, const FilePath& filePath)
{
	trackNumber_ = trackNumber;
	title_ = title;
	artist_ = artist;
	album_ = album;
	filePath_ = filePath;
}

Song::~Song()
{
}


unsigned int Song::getTrackNumber() const
{
	return trackNumber_;
}

void Song::setTrackNumber(const unsigned int& trackNumber)
{
	trackNumber_ = trackNumber;
}

wstring Song::getTitle() const
{
	return title_;
}

void Song::setTitle(const wstring& title)
{
	title_ = title;
}

wstring Song::getArtist() const
{
	return artist_;
}

void Song::setArtist(const wstring& artist)
{
	artist_ = artist;
}

wstring Song::getAlbum() const
{
	return album_;
}

void Song::setAlbum(const wstring& album)
{
	album_ = album;
}

FilePath Song::getFilePath() const
{
	return filePath_;
}

void Song::setFilePath(const FilePath& filePath)
{
	filePath_ = filePath;
}
