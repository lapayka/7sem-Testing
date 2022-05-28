#pragma once
#include "../DBCW/IMusRepository.h"
#include "../../SQLlite/sqlite3.h"
#include <functional>
#include <exception>

typedef std::function<void* (int, char**, char**)> sql_handler;

class LtMusRepo :
    public IMusRepository
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
    LtMusRepo (sqlite3* _conn) : conn(_conn) {}

    virtual void update(const string& uId, int mId) override {
        string query("select * from uc where usId = '" + uId + "' and muid = " + to_string(mId) + ";");
        char* error;

        int columns = 0;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
                columns = argc;
            }, error))
            throw std::exception(error);    

        if (columns > 0)
        {
            query = string("BEGIN;"
                "UPDATE UC SET audRate = audRate + 1 " "where usid = '" + uId + "' and MuId = " + to_string(mId) + ";"
                "UPDATE MusComps SET audRate = audRate + 1  where Id = " + to_string(mId) + ";"
                "COMMIT;");
        }
        else
        {
            query = string("BEGIN;"
                "insert into UC(usid, muid, audrate) values('" + uId + "', " + to_string(mId) + ", 1); "
                "UPDATE MusComps SET audRate = audRate + 1  where Id = " + to_string(mId) + "; "
                "COMMIT;");
        }

        if (SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
            throw std::exception(error);
    }

    virtual vector<MusItem> getMusByName(const string& name) override { 
        std::vector<MusItem> res;

        PGresult* pgRes;

        std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
            "from           MusComps m"
            "               join Albums al on m.AlId = al.id "
            "               join Artists ar on al.ArId = ar.email "
            "               where m.name = '" + name + "';");

        char* error = nullptr;
        if (SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
            throw std::exception(error);

        std::vector<MusItem> result;

        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
            result.emplace_back<MusItem>({ stoi(argv[0]), argv[1] , argv[2], argv[3], argv[4]});
            }, error))
            throw std::exception(error);


        return res;
    }

};

