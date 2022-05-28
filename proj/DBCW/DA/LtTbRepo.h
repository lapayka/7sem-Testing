#pragma once
#include "../DBCW/ITablesRepository.h"
#include "../../SQLlite/sqlite3.h"
#include <functional>
#include <exception>

typedef std::function<void* (int, char**, char**)> sql_handler;

class LtTbRepo :
    public ITablesRepository
{
private:
	sqlite3* conn;

    static int callback(void* p_data, int num_fields, char** p_fields, char** p_col_names) {
        (*reinterpret_cast<sql_handler*>(p_data))(num_fields, p_fields, p_col_names);
        return 0;
    }

    int Data(sqlite3* handle, const char* request, sql_handler h, char* error) {
        return sqlite3_exec(handle, request, callback, reinterpret_cast<void*>(&h), &error);
    }

public:
	LtTbRepo(sqlite3* _conn) : conn(_conn) {}

public:
	virtual std::vector<MusItem> getMusByArtist(const string& id) override {
        std::vector<MusItem> res;

        std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
            "from MusComps m join Albums al on m.AlId = al.id "
            "join Artists ar on al.ArId = ar.email "
            "where ar.email = '" + id + "';");

        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
            res.emplace_back<MusItem>({ stoi(argv[0]), argv[1] , argv[2], argv[3], argv[4] });
            }, error))
            throw std::exception(error);       

        return res;
	}

	virtual std::vector<MusItem> getMusByAlbum(int id) override {
        std::vector<MusItem> res;

        std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
            "from MusComps m join Albums al on m.AlId = al.id "
            "join Artists ar on al.ArId = ar.email "
            "where al.id = " + to_string(id) + ";");

        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
            res.emplace_back<MusItem>({ stoi(argv[0]), argv[1] , argv[2], argv[3], argv[4] });
            }, error))
            throw std::exception(error);

        return res;
    }
	virtual std::vector<MusItem> getMusByPlaylist(int id) override {
        std::vector<MusItem> res;

        std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
            "from Playlists pl join PM pc on pl.id = pc.PlId "
            "               join MusComps m on pc.MuId = m.id "
            "               join Albums al on m.AlId = al.id "
            "               join Artists ar on al.ArId = ar.email "
            "               where pl.id = " + to_string(id) + ";");

        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
            res.emplace_back<MusItem>({ stoi(argv[0]), argv[1] , argv[2], argv[3], argv[4] });
            }, error))
            throw std::exception(error);

        return res;
    }
	virtual std::vector<PlstItem> getPlaylistsByUser(const string& id) override {
        std::vector<PlstItem> res;   

        std::string query("select distinct pl.id as id, pl.name as name "
            "from Playlists pl join UP on pl.id = up.PlId "
            "               join Users u on u.email = up.UsId "
            "               where u.email = '" + id + "' ;");

        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
            res.emplace_back<PlstItem>({ stoi(argv[0]), argv[1] });
            }, error))
            throw std::exception(error);

        return res;
    }
};
