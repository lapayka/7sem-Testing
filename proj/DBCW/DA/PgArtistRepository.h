#pragma once
#include "IArtistRepository.h"
#include "libpq-fe.h"

#include <vector>
#include <string>

using namespace std;

class PgArtistRepository :
    public IArtistRepository
{
private:
	PGconn* connect;
public:
	PgArtistRepository(PGconn* _connect) : connect(_connect){};

	virtual void createRequest(const string& UsId, const string &name) override
	{
		string query("Insert into ArtistRequest(usid, state, name) values('" + UsId + "', 'active', '" + name + "'); ");

		PGresult *res = PQexec(connect, query.c_str());
		PQclear(res);
	}

	virtual vector<pair<string, string>> getAllRequests() override
	{
		string query("select * from ArtistRequest where state = 'active';");

		PGresult *res = PQexec(connect, query.c_str());


		vector<pair<string, string>> result;
		for (int i = 0; i < PQntuples(res); i++)
		{
			int e_num = PQfnumber(res, "usid");
			int n_num = PQfnumber(res, "name");
			char* name = PQgetvalue(res, i, n_num);
			char* email = PQgetvalue(res, i, e_num);
			result.push_back(make_pair<string, string>(string(email), string(name)));
		}

		PQclear(res);

		return result;
	};

	virtual std::vector<std::string> getArtistsByName(const std::string& name) override
	{
		std::vector<std::string> result;
		std::string query("select email from artists where name = '" + name + "';");
		PGresult* pgRes = PQexec(connect, query.c_str());

        for (int i = 0; i < PQntuples(pgRes); i++)
        {
            int n_num = PQfnumber(pgRes, "email");
            char* name = PQgetvalue(pgRes, i, n_num);

			result.push_back(string(name));
		}

		PQclear(pgRes);

		return result;
	};
	virtual void createArtist(const std::string& email, const std::string& password, const std::string& name) override
	{
		std::string query(""
			             "insert into artists(email, password, name) values ('" + email + "', '" + password + "', '" + name + "');"
						 "");
		PGresult * res = PQexec(connect, query.c_str());
		PQclear(res);
	};
};

