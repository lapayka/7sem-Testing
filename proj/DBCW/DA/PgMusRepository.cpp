#include "PgMusRepository.h"


std::vector<MusItem> PgMusRepository::getMusByName(const string &name)
{
    std::vector<MusItem> res;

    PGresult* pgRes;

    std::string query("select m.id, m.name, m.duration, m.path, al.name as albumName, ar.name as artistName "
        "from           MusComps m"
        "               join Albums al on m.AlId = al.id "
        "               join Artists ar on al.ArId = ar.email "
        "               where m.name = '" + name + "';");

    pgRes = PQexec(connection, query.c_str());

    res = getMusTableFromRes(pgRes);

    PQclear(pgRes);

    return res;
}

std::vector<MusItem> PgMusRepository::getMusTableFromRes(PGresult* pgRes)
{
    std::vector<MusItem> result;

    for (int i = 0; i < PQntuples(pgRes); i++)
    {
        int i_num = PQfnumber(pgRes, "id");
        int n_num = PQfnumber(pgRes, "name");
        int d_num = PQfnumber(pgRes, "duration");
        int al_num = PQfnumber(pgRes, "albumName");
        int ar_num = PQfnumber(pgRes, "artistName");
        int path_num = PQfnumber(pgRes, "path");

        char* id = PQgetvalue(pgRes, i, i_num);
        char* name = PQgetvalue(pgRes, i, n_num);
        char* duration = PQgetvalue(pgRes, i, d_num);
        char* alName = PQgetvalue(pgRes, i, al_num);
        char* arName = PQgetvalue(pgRes, i, ar_num);
        char* path = PQgetvalue(pgRes, i, path_num);

        result.push_back(
            MusItem(
                atoi(id),
                string(name),
                string(duration),
                string(alName),
                string(arName),
                string(path)));
    }
    return result;
}