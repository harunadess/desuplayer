#ifndef SONG_H
#define SONG_H

#include <string>
#include "filePath.h"

using std::wstring;
using std::string;

class Song
{
public:
	Song();
	Song(const unsigned int& trackNumber, const wstring& title, const wstring& artist, const wstring& album, const FilePath& filePath);
	~Song();

	unsigned int getTrackNumber() const;
	void setTrackNumber(const unsigned int& trackNumber);
	wstring getTitle() const;
	void setTitle(const wstring& title);
	wstring getArtist() const;
	void setArtist(const wstring& artist);
	wstring getAlbum() const;
	void setAlbum(const wstring& album);
	FilePath getFilePath() const;
	void setFilePath(const FilePath& filePath);

private:
	unsigned int trackNumber_;
	wstring title_;
	wstring artist_;
	wstring album_;
	FilePath filePath_;

};

#endif // !SONG_H
