#pragma once
#include "../DBCW/IPlaylistRepository.h"
#include "../../SQLlite/sqlite3.h"
#include <functional>
#include <exception>

typedef std::function<void* (int, char**, char**)> sql_handler;

class LtPlstRepo :
    public IPlaylistRepository
{
private:
	sqlite3* conn;
public:
	LtPlstRepo(sqlite3* _conn) : conn(_conn) {}
public:
	virtual void create(const string& nam, const string& user) override {}

	virtual void del(int id) override {
		string query("BEGIN; "
			"DELETE from PM where PlId = " + to_string(id) + "; "
			"DELETE from UP where PlId = " + to_string(id) + "; "
			"DELETE from PLAYLISTS where id = " + to_string(id) + "; "
			"COMMIT;"
		);

		char* error = nullptr;
		if (SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
			throw std::exception(error);
	}

	virtual void aUpdate(const MusItem& item, int id) override {
		string query("insert into pm(PlId, MuId) values (" + to_string(id) + ", " + to_string(item.id) + ");");

		char* error = nullptr;
		if (SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
			throw std::exception(error);
	}
};

