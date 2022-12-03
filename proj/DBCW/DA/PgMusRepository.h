#pragma once
#include "IMusRepository.h"
#include "libpq-fe.h"
class PgMusRepository :
    public IMusRepository
{
private:
    PGconn* connection;
public:
    PgMusRepository(PGconn* _connection) : connection(_connection) {}

    virtual vector<MusItem> getMusByName(const string& name) override;

    virtual void update(const string& uId, int mId) override
    {
        string query("select * from uc where usId = '" + uId + "' and muid = " + to_string(mId) + ";");
        PGresult* res = PQexec(connection, query.c_str());

        if (PQntuples(res) > 0)
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
                "UPDATE MusComps SET audRate = audRate + 1  where Id = " + to_string(mId) +  "; "
                "COMMIT;");
        }

        PGresult* res2 = PQexec(connection, query.c_str());
        PQclear(res);
        PQclear(res2);
    };
private:
    std::vector<MusItem> getMusTableFromRes(PGresult* pgRes);
};

