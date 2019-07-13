#include "playlist.h"

using std::vector;
using std::wstring;

Playlist::Playlist()
{
	m_title = L"";
	m_songList = vector<Song>();
	m_listIndex = 0;
}

Playlist::Playlist(const wstring& title)
	:m_title(title)
{
	m_songList = vector<Song>();
	m_listIndex = 0;
}

Playlist::~Playlist()
{
}

wstring Playlist::getTitle() const
{
	return m_title;
}

void Playlist::setTitle(const wstring& title)
{
	m_title = title;
}

vector<Song> Playlist::getSongList() const
{
	return m_songList;
}

void Playlist::setSongList(const vector<Song>& songList)
{
	m_songList = songList;
}

void Playlist::addSongToList(const Song& song)
{
	m_songList.push_back(song);
}

void Playlist::addAllToList(vector<Song>& list)
{
	for (vector<Song>::iterator it = list.begin(); it != list.end(); ++it)
		addSongToList(*it);
}

void Playlist::addContentsToList(const Album& album)
{
	vector<Song> toAdd = album.getTrackList();
	addAllToList(toAdd);
}

void Playlist::addContentsToList(const Artist& artist)
{
	std::map<wstring, vector<Song>> albums = artist.getAlbums();
	vector<wstring> albumTitles = artist.getAllAlbumTitles();

	for (vector<wstring>::iterator it = albumTitles.begin(); it != albumTitles.end(); ++it)
	{
		vector<Song> album = artist.getAlbumName(*it);
		addAllToList(album);
	}
}

void Playlist::addContentsToList(const Playlist& playlist)
{
	vector<Song> listContents = playlist.getSongList();
	addAllToList(listContents);
}

bool Playlist::getNext(Song &song)
{
	if (m_listIndex >= 0 && m_listIndex < m_songList.size())
	{
		song = m_songList.at(m_listIndex++);
		return true;
	}
	return false;
}

bool Playlist::hasNext()
{
	size_t size = m_songList.size();
	return (size > 0) && (m_listIndex < size);
}

void Playlist::clear()
{
	bool succ = m_songList.empty();
	m_listIndex = 0;
}
