#pragma once
#include "../DBCW/IPlaylistRepository.h"
#include <sqlite3.h>
class LtPlstRepo :
    public IPlaylistRepository
{
private:
	sqlite3* conn;
public:
	LtPlstRepo(sqlite3* _conn) : conn(_conn) {}
public:
	virtual void create(const string& nam, const string& user) override {}
	virtual void del(int id) override {}
	virtual void aUpdate(const MusItem& item, int id) override {}
};

