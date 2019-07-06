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

void MusicLibrary::setAlbums(const map<wstring, Album>& albums)
{
	albums_ = albums;
}

void MusicLibrary::setSongs(const map<wstring, Song>& songs)
{
	songs_ = songs;
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

Album MusicLibrary::getAlbum(const wstring& albumName) const
{
	try
	{
		return albums_.at(albumName);
	}
	catch (const std::out_of_range e)
	{
		printf_s("%s: %s\n", "Couldn't find album ", e.what());
		return Album();
	}
}

Song MusicLibrary::getSong(const wstring& songTitle) const
{
	try
	{
		return songs_.at(songTitle);
	}
	catch (const std::out_of_range e)
	{
		printf_s("%s: %s\n", "Couldn't find album ", e.what());
		return Song();
	}
}

bool MusicLibrary::unifiedSearch(const wstring& searchTerms, SearchResults& searchResults) const
{
	wstring nSearchTerms = wstringToLower(searchTerms);
	try
	{
		searchResults.artists = searchArtists_(nSearchTerms);
		searchResults.albums = searchAlbums_(nSearchTerms);
		searchResults.songs = searchSongs_(nSearchTerms);
	}
	catch (std::exception e)
	{
		std::wcerr << L"Error in musicLibrary::unifiedSearch : " << e.what() << std::endl;
		return false;
	}
	return true;
}

vector<Artist> MusicLibrary::searchArtists_(const wstring& searchTerms) const
{
	vector<Artist> res;

	for (auto& artistPair : artists_)
	{
		Artist artist = artistPair.second;
		wstring nArtistName = wstringToLower(artist.getName());

		if (nArtistName.find(searchTerms) != wstring::npos)
			res.push_back(artist);
	}

	return res;
}

vector<Album> MusicLibrary::searchAlbums_(const wstring& searchTerms) const
{
	vector<Album> res;

	for (auto& albumPair : albums_)
	{
		Album album = albumPair.second;
		wstring nAlbumTitle = wstringToLower(album.getTitle());
		wstring nAlbumArtist = wstringToLower(album.getArtistName());

		if ((nAlbumTitle.find(searchTerms) != wstring::npos) || 
			(nAlbumArtist.find(searchTerms) != wstring::npos))
			res.push_back(album);

		return res;
	}
}

vector<Song> MusicLibrary::searchSongs_(const wstring& searchTerms) const
{
	vector<Song> res;
	
	for (auto& songPair : songs_)
	{
		Song song = songPair.second;
		wstring nSongTitle = wstringToLower(song.getTitle());
		wstring nAlbumArtist = wstringToLower(song.getArtist());
		wstring nAlbumTitle = wstringToLower(song.getAlbum());

		if ((nSongTitle.find(searchTerms) != wstring::npos) ||
			(nAlbumArtist.find(searchTerms) != wstring::npos) ||
			(nAlbumTitle.find(searchTerms) != wstring::npos))
			res.push_back(song);
	}

	return res;
}
