#pragma once
#include "../DBCW/IUserRepo.h"
#include <sqlite3.h>
class LtUsRepo :
    public IUserRepo
{
private:
	sqlite3* conn;
public:
	LtUsRepo(sqlite3* _conn) : conn(_conn) {}

	virtual std::pair<std::string, std::string> UserInfo(const std::string& id) override {}

	virtual bool login(const string& email, const string& password) override {}
};



