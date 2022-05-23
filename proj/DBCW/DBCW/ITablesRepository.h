#pragma once
#include <vector>
#include "MusItem.h"
#include <string>
#include "PlstItem.h"
class ITablesRepository
{
public:
	virtual std::vector<MusItem> getMusByArtist(const string &id) = 0;
	virtual std::vector<MusItem> getMusByAlbum(int id) = 0;
	virtual std::vector<MusItem> getMusByPlaylist(int id) = 0;
	virtual std::vector<PlstItem> getPlaylistsByUser(const string& id) = 0;

};

