#pragma once
#include "../DBCW/IAlbumsRepository.h"
#include <sqlite3.h>
class LtAlRepo :
    public IAlbumsRepository
{
private:
	sqlite3* conn;
public:
	LtAlRepo(sqlite3* _conn) : conn(_conn) {}
public:
	virtual void create(const std::vector<MusItem>& items, const std::string& name, const std::string& arId) 
	{

	}
	virtual void alDelete(int id) {}
	virtual std::vector<int> getAlbumsByName(const std::string& name) {}
};

