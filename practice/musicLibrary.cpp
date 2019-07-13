#include "musicLibrary.h"

#include "util.h"

using std::map;
using std::vector;
using std::wstring;

MusicLibrary::MusicLibrary()
{
	m_artistMap = map<wstring, Artist>();
	m_playlistList = vector<Playlist>();
}

MusicLibrary::~MusicLibrary()
{
}

map<wstring, Artist> MusicLibrary::getArtistMap() const
{
	return m_artistMap;
}

void MusicLibrary::setArtistMap(const map<wstring, Artist>& artists)
{
	m_artistMap = artists;
}

void MusicLibrary::setAlbumMap(const map<wstring, Album>& albums)
{
	m_albumMap = albums;
}

void MusicLibrary::setSongMap(const map<wstring, Song>& songs)
{
	m_songMap = songs;
}

Artist MusicLibrary::getArtistName(const wstring& artistName) const
{
	try
	{
		return m_artistMap.at(artistName);
	}
	catch (const std::out_of_range e)
	{
		std::wcerr << "Couldn't find artist " << e.what() << std::endl;
		return Artist();
	}
}

Album MusicLibrary::getAlbumName(const wstring& albumName) const
{
	try
	{
		return m_albumMap.at(albumName);
	}
	catch (const std::out_of_range e)
	{
		std::wcerr << "Couldn't find album " << e.what() << std::endl;
		return Album();
	}
}

Song MusicLibrary::getSong(const wstring& songTitle) const
{
	try
	{
		return m_songMap.at(songTitle);
	}
	catch (const std::out_of_range e)
	{
		std::wcerr << "Couldn't find song " << e.what() << std::endl;
		return Song();
	}
}

bool MusicLibrary::fullSearch(const wstring& searchTerms, SearchResults& searchResults) const
{
	wstring nSearchTerms = wstringToLower(searchTerms);
	try
	{
		searchResults.artists = searchArtists(nSearchTerms);
		searchResults.albums = searchAlbums(nSearchTerms);
		searchResults.songs = searchSongs(nSearchTerms);
	}
	catch (std::exception e)
	{
		std::wcerr << L"Error in musicLibrary::fullSearch : " << e.what() << std::endl;
		return false;
	}
	return true;
}

vector<Artist> MusicLibrary::searchArtists(const wstring& searchTerms) const
{
	vector<Artist> res;

	for (auto& artistPair : m_artistMap)
	{
		Artist artist = artistPair.second;
		wstring nArtistName = wstringToLower(artist.getName());

		if (nArtistName.find(searchTerms) != wstring::npos)
			res.push_back(artist);
	}

	return res;
}

vector<Album> MusicLibrary::searchAlbums(const wstring& searchTerms) const
{
	vector<Album> res;

	for (auto& albumPair : m_albumMap)
	{
		Album album = albumPair.second;
		wstring nAlbumTitle = wstringToLower(album.getTitle());
		wstring nAlbumArtist = wstringToLower(album.getArtistName());

		if ((nAlbumTitle.find(searchTerms) != wstring::npos) || (nAlbumArtist.find(searchTerms) != wstring::npos))
			res.push_back(album);
	}

	return res;
}

vector<Song> MusicLibrary::searchSongs(const wstring& searchTerms) const
{
	vector<Song> res;
	
	for (auto& songPair : m_songMap)
	{
		Song song = songPair.second;
		wstring nSongTitle = wstringToLower(song.getTitle());
		wstring nAlbumArtist = wstringToLower(song.getArtistName());
		wstring nAlbumTitle = wstringToLower(song.getAlbumTitle());

		if ((nSongTitle.find(searchTerms) != wstring::npos) || (nAlbumArtist.find(searchTerms) != wstring::npos) ||
			(nAlbumTitle.find(searchTerms) != wstring::npos))
			res.push_back(song);
	}

	return res;
}

bool MusicLibrary::populate(wstring& baseDir)
{
	bool populateSucc = m_songregator.populateLibrary(baseDir, m_artistMap, m_albumMap, m_songMap);

	if (populateSucc)
		m_baseDir = baseDir;

	return populateSucc;
}
