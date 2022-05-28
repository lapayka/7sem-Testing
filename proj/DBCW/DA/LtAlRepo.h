#pragma once
#include "../DBCW/IAlbumsRepository.h"
#include "../../SQLlite/sqlite3.h"
#include <functional>
#include <exception>

typedef std::function<void* (int, char**, char**)> sql_handler;

class LtAlRepo :
    public IAlbumsRepository
{
private:
	sqlite3* conn = nullptr;

    static int callback(void* p_data, int num_fields, char** p_fields, char** p_col_names) {
        (*reinterpret_cast<sql_handler*>(p_data))(num_fields, p_fields, p_col_names);
        return 0;
    }

    int Data(sqlite3* handle, const char* request, sql_handler h, char* error) {
        return sqlite3_exec(handle, request, callback, reinterpret_cast<void*>(&h), &error);
    }

public:
	LtAlRepo(sqlite3* _conn) : conn(_conn) {}
public:
	virtual void create(const std::vector<MusItem>& items, const std::string& name, const std::string& arId) { }

	virtual void alDelete(int id) { }

	virtual std::vector<int> getAlbumsByName(const std::string& name) {
        std::vector<int> result;
        std::string query("select id from albums where name = '" + name + "';");
        
        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
                result.emplace_back(stoi(argv[0]));
            }, error))
            throw std::exception(error);

        return result;
    }
};

