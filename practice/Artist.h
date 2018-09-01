#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <map>
#include <vector>
#include "song.h"

using std::map;
using std::vector;
using std::wstring;

class Artist
{
public:
	Artist();
	Artist(const wstring& name);
	Artist(const wstring& name, const map<wstring, vector<Song>>& albums);
	~Artist();

	wstring getName() const;
	void setName(const wstring& name);
	map<wstring, vector<Song>> getAlbums() const;
	void setAlbums(const map<wstring, vector<Song>>& albums);
	void addSongToAlbum(const wstring& album, const Song& song);
	vector<Song> getAlbum(const wstring& album) const;

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(name_, albums_);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		archive(name_, albums_);
	}

private:
	wstring name_;
	map<wstring, vector<Song>> albums_;

};

#endif // !ARTIST_H
