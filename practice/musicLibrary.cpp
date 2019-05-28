#include "musicLibrary.h"

MusicLibrary::MusicLibrary()
{
	artists_ = map<wstring, Artist>();
	playlists_ = vector<Playlist>();
}

MusicLibrary::~MusicLibrary()
{
}

map<wstring, Artist> MusicLibrary::getArtists() const
{
	return artists_;
}

void MusicLibrary::setArtists(const map<wstring, Artist>& artists)
{
	artists_ = artists;
}

Artist MusicLibrary::getArtist(const wstring& artistName) const
{
	try
	{
		return artists_.at(artistName);
	}
	catch (const std::out_of_range e)
	{
		printf_s("%s: %s\n", "Couldn't find album ", e.what());
		return Artist();
	}
}