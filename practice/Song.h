#ifndef SONG_H
#define SONG_H

#include <string>

#include "filePath.h"
#include "audioProperties.h"

class Song
{
public:
	Song();
	Song(const unsigned int& trackNumber, const std::wstring& title, const std::wstring& artist, const std::wstring& album, 
		const std::wstring& genre, const AudioProperties audioProperties, const FilePath& filePath);
	~Song();

	//todo: sets and gets
	unsigned int getTrackNumber() const;
	void setTrackNumber(const unsigned int& trackNumber);
	std::wstring getTitle() const;
	void setTitle(const std::wstring& title);
	std::wstring getArtistName() const;
	void setArtistName(const std::wstring& artist);
	std::wstring getAlbumTitle() const;
	void setAlbumTitle(const std::wstring& album);
	FilePath getFilePath() const;
	void setFilePath(const FilePath& filePath);

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(m_trackNumber, m_title, m_artistName, m_albumTitle, m_genre, m_audioProperties, m_filePath);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_trackNumber, m_title, m_artistName, m_albumTitle, m_genre, m_audioProperties, m_filePath);
	}

private:
	unsigned int m_trackNumber;
	std::wstring m_title;
	std::wstring m_artistName;
	std::wstring m_albumTitle;
	std::wstring m_genre;
	AudioProperties m_audioProperties;
	FilePath m_filePath;

};

#endif // !SONG_H
