#pragma once
#include "../DBCW/PgArtistRepository.h"
#include <sqlite3.h>
class LtArRepo :
    public IArtistRepository
{
private:
	sqlite3* conn;
public:
	LtArRepo(sqlite3* _conn) : conn(_conn) {}
public:
	virtual void createRequest(const string& UsId, const string& name) override {}
	virtual vector<pair<string, string>> getAllRequests() override {}
	virtual std::vector<std::string> getArtistsByName(const std::string& name) override {}
	virtual void createArtist(const std::string& email, const std::string& password, const std::string& name) override {}
};

