#pragma once
#include "../DBCW/PgArtistRepository.h"
#include "../../SQLlite/sqlite3.h"
#include <functional>
#include <exception>

typedef std::function<void* (int, char**, char**)> sql_handler;

class LtArRepo :
    public IArtistRepository
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
	LtArRepo(sqlite3* _conn) : conn(_conn) {}
public:
	virtual void createRequest(const string& UsId, const string& name) override {
		string query("Insert into ArtistRequest(usid, state, name) values('" + UsId + "', 'active', '" + name + "'); ");

		char* error = nullptr;
		if(SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
			throw std::exception(error);
	}

	virtual vector<pair<string, string>> getAllRequests() override {
		string query("select * from ArtistRequest where state = 'active';");

		vector<pair<string, string>> result;
		char* error = nullptr;

		if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
			result.emplace_back<std::pair<std::string, std::string>>( { argv[1], argv[2] } );
			}, error))
			throw std::exception(error);	

		return result;
	}

	virtual std::vector<std::string> getArtistsByName(const std::string& name) override {
		std::vector<std::string> result;
		std::string query("select email from artists where name = '" + name + "';");

		char* error = nullptr;

		if (SQLITE_OK != Data(conn, query.c_str(), [&](int argc, char** argv, char** col) -> void* {
			result.emplace_back(argv[1]);
			}, error))
			throw std::exception(error);		

		return result;
	}
	virtual void createArtist(const std::string& email, const std::string& password, const std::string& name) override {
		std::string query("BEGIN;"
			"insert into artists(email, password, name) values ('" + email + "', '" + password + "', '" + name + "');"
			"update artistRequest set state = 'accepted' where usid = '" + email + "';"
			"COMMIT;");
		char* error = nullptr;
		if (SQLITE_OK != sqlite3_exec(conn, query.c_str(), nullptr, nullptr, &error))
			throw std::exception(error);
	}
};

