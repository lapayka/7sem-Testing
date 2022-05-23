#pragma once
#include "../DBCW/ITablesRepository.h"
#include <sqlite3.h>

class LtTbRepo :
    public ITablesRepository
{
private:
	sqlite3* conn;
public:
	LtTbRepo(sqlite3* _conn) : conn(_conn) {}

public:
	virtual std::vector<MusItem> getMusByArtist(const string& id) override {}
	virtual std::vector<MusItem> getMusByAlbum(int id) override {}
	virtual std::vector<MusItem> getMusByPlaylist(int id) override {}
	virtual std::vector<PlstItem> getPlaylistsByUser(const string& id) override {}
};



