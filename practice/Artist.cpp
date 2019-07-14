#include "Artist.h"

#include <iostream>

using std::vector;
using std::map;
using std::wstring;

Artist::Artist()
{
	m_name = L"";
	m_albumTitles = vector<wstring>();
	m_albumMap = map<wstring, vector<Song>>();
}

Artist::Artist(const wstring name)
	:m_name(name)
{
	m_albumTitles = vector<wstring>();
	m_albumMap = map<wstring, vector<Song>>();
}

Artist::Artist(const wstring name, const map<wstring, vector<Song>> albumMap)
	:m_name(name), m_albumMap(albumMap)
{
	m_albumTitles = vector<wstring>();
}

Artist::~Artist()
{
}

wstring Artist::getName() const
{
	return m_name;
}

void Artist::setName(const wstring& name)
{
	m_name = name;
}

map<wstring, vector<Song>> Artist::getAlbums() const
{
	return m_albumMap;
}

void Artist::setAlbumMap(const map<wstring, vector<Song>>& albums)
{
	m_albumMap = albums;
}

void Artist::addSongToAlbum(const wstring& album, const Song& song)
{
	m_albumTitles.push_back(album);
	m_albumMap[album].push_back(song);
}

vector<Song> Artist::getAlbumName(const wstring& album) const
{
	try 
	{
		return m_albumMap.at(album);
	}
	catch (const std::out_of_range e)
	{
		std::wcerr << L"Couldn't find album: " << album << std::endl;
		return vector<Song>();
	}
}

vector<wstring> Artist::getAllAlbumTitles() const
{
	return m_albumTitles;
}

void Artist::addAlbumToList(const wstring albumKey, const wstring albumName, const vector<Song> album)
{
	std::pair<wstring, vector<Song>> ap(albumKey, album);
	m_albumMap.insert(ap);

	m_albumTitles.push_back(albumName);
}
