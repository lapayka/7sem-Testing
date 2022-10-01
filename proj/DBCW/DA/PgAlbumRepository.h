#pragma once
#include "IAlbumsRepository.h"
#include "libpq-fe.h"
class PgAlbumRepository :
    public IAlbumsRepository
{
public:
    PgAlbumRepository(PGconn *_conn) : conn(_conn) {}

    virtual void create(const std::vector<MusItem>& items, const std::string & name, const std::string& arId) override
    {
        {
            std::string query("BEGIN;");
            PGresult* pgRes = PQexec(conn, query.c_str());
            PQclear(pgRes);
        }

        std::string query("select * from fn_add_album('" + name + "', '" + arId + "');");
        PGresult* pgRes = PQexec(conn, query.c_str());

        int n_num = PQfnumber(pgRes, "album_id");
        int al_id = stoi(PQgetvalue(pgRes, 0, n_num));

        PQclear(pgRes);


        for (const auto& item : items)
        {
            std::string query("insert into muscomps(name, audRate, duration, AlId) values ('" + item.name + "', 0, '" + item.duration + "', " + to_string(al_id) + ");");
            pgRes = PQexec(conn, query.c_str());
            PQclear(pgRes);
        }

        {
            std::string query("COMMIT;");
            PGresult* pgRes = PQexec(conn, query.c_str());
            PQclear(pgRes);
        }
    }
    virtual void alDelete(int id) override
    {
        std::string query("BEGIN;"
                           "delete from uc where muid in (select id from muscomps where alid = " + to_string(id) + ");"
                           "delete from pm where muid in (select id from muscomps where alid = " + to_string(id) + ");"
                           "delete from musComps where alid = " + to_string(id) + ";" +
                           "delete from albums where id = " + to_string(id) + ";"
                           "COMMIT;");
        PGresult* pgRes = PQexec(conn, query.c_str());

        PQclear(pgRes);
    }
    virtual std::vector<int> getAlbumsByName(const std::string& name) override
    {
        std::vector<int> result;
        std::string query("select id from albums where name = '" + name + "';");
        PGresult* pgRes = PQexec(conn, query.c_str());

        for (int i = 0; i < PQntuples(pgRes); i++)
        {
            int n_num = PQfnumber(pgRes, "id");
            char* name = PQgetvalue(pgRes, i, n_num);

            result.push_back(stoi(name));
        }

        PQclear(pgRes);

        return result;
    }
private:
    PGconn* conn;
};

