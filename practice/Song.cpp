#include "song.h"

using std::wstring;

Song::Song()
{
	m_trackNumber = 0;
	m_title = L"";
	m_artistName = L"";
	m_albumTitle = L"";
}

Song::Song(const unsigned int& trackNumber, const std::wstring& title, const std::wstring& artist, const std::wstring& album, 
			const std::wstring& genre, const AudioProperties audioProperties, const FilePath& filePath)
	:m_trackNumber(trackNumber), m_title(title), m_artistName(artist), m_albumTitle(album), m_genre(genre),
		m_audioProperties(audioProperties), m_filePath(filePath)
{
}

Song::~Song()
{
}


unsigned int Song::getTrackNumber() const
{
	return m_trackNumber;
}

void Song::setTrackNumber(const unsigned int& trackNumber)
{
	m_trackNumber = trackNumber;
}

wstring Song::getTitle() const
{
	return m_title;
}

void Song::setTitle(const wstring& title)
{
	m_title = title;
}

wstring Song::getArtistName() const
{
	return m_artistName;
}

void Song::setArtistName(const wstring& artistName)
{
	m_artistName = artistName;
}

wstring Song::getAlbumTitle() const
{
	return m_albumTitle;
}

void Song::setAlbumTitle(const wstring& albumTitle)
{
	m_albumTitle = albumTitle;
}

FilePath Song::getFilePath() const
{
	return m_filePath;
}

void Song::setFilePath(const FilePath& filePath)
{
	m_filePath = filePath;
}
