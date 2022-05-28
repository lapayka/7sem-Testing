#pragma once
#include "../DBCW/IUserRepo.h"
#include "../../SQLlite/sqlite3.h"
#include <functional>
#include <exception>

typedef std::function<void* (int, char**, char**)> sql_handler;

class LtUsRepo :
    public IUserRepo
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
	LtUsRepo(sqlite3* _conn) : conn(_conn) {}

	virtual std::pair<std::string, std::string> UserInfo(const std::string& id) override {
        std::string query("select * from Users where email = '" + id + "';");

        std::pair<std::string, std::string> result;

        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
                result = { argv[1], argv[2] };
            }, error))
            throw std::exception(error);
	}

	virtual bool login(const string& email, const string& password) override {
        std::string query("select * from Users where email = '" + email + "';");

        bool ret = true;

        char* error = nullptr;
        if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
                ret = argc > 0;
            }, error))
            throw std::exception(error);


        if (!ret)
            return ret;

       
        std::string query("insert into users(email, password) values('" + email + "', '" + password + "');");
        if (SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
            throw std::exception(error);
       

        return ret;
    }
};



