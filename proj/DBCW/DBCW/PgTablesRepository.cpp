#include "PgTablesRepository.h"

std::vector<MusItem> PgTablesRepository::getMusByArtist(const string& id)
{
    std::vector<MusItem> res;

    PGresult* pgRes;

    std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
        "from MusComps m join Albums al on m.AlId = al.id "
        "join Artists ar on al.ArId = ar.email "
        "where ar.email = '" + id + "'"
        "order by m.audrate;");

    pgRes = PQexec(connPtr, query.c_str());
                            
    res = getMusTableFromRes(pgRes);

    PQclear(pgRes);
    
    return res;
}

std::vector<MusItem> PgTablesRepository::getMusByAlbum(int id)
{
    std::vector<MusItem> res;

    PGresult* pgRes;

    std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
        "from MusComps m join Albums al on m.AlId = al.id "
        "join Artists ar on al.ArId = ar.email "
        "where al.id = " + to_string(id) +
        " order by m.audrate;");

    pgRes = PQexec(connPtr, query.c_str());

    res = getMusTableFromRes(pgRes);

    PQclear(pgRes);

    return res;
}

std::vector<MusItem> PgTablesRepository::getMusByPlaylist(int id)
{
    std::vector<MusItem> res;

    PGresult* pgRes;

    std::string query("select m.id, m.name, m.duration, al.name as albumName, ar.name as artistName "
                      "from Playlists pl join PM pc on pl.id = pc.PlId "
                      "               join MusComps m on pc.MuId = m.id "
                      "               join Albums al on m.AlId = al.id "
                      "               join Artists ar on al.ArId = ar.email "
                      "               where pl.id = " + to_string(id) + 
                      "               order by m.audrate;");

    pgRes = PQexec(connPtr, query.c_str());

    res = getMusTableFromRes(pgRes);

    PQclear(pgRes);

    return res;
}

std::vector<PlstItem> PgTablesRepository::getPlaylistsByUser(const string& id)
{
    std::vector<PlstItem> res;

    PGresult* pgRes;

    std::string query("select distinct pl.id as id, pl.name as name "
        "from Playlists pl join UP on pl.id = up.PlId "
        "               join Users u on u.email = up.UsId "
        "               where u.email = '" + id + "' ;");

    pgRes = PQexec(connPtr, query.c_str());

    res = getPlstTableFromRes(pgRes);

    PQclear(pgRes);

    return res;
}

std::vector<MusItem> PgTablesRepository::getMusTableFromRes(PGresult* pgRes)
{
    std::vector<MusItem> result;

    for (int i = 0; i < PQntuples(pgRes); i++)
    {
        int i_num = PQfnumber(pgRes, "id");
        int n_num = PQfnumber(pgRes, "name");
        int d_num = PQfnumber(pgRes, "duration");
        int al_num = PQfnumber(pgRes, "albumName");
        int ar_num = PQfnumber(pgRes, "artistName");

        char* id = PQgetvalue(pgRes, i, i_num);
        char* name = PQgetvalue(pgRes, i, n_num);
        char* duration = PQgetvalue(pgRes, i, d_num);
        char* alName = PQgetvalue(pgRes, i, al_num);
        char* arName = PQgetvalue(pgRes, i, ar_num);

        result.push_back(
            MusItem(
                atoi(id), 
                string(name),
                string(duration),
                string(alName),
                string(arName)));
    }
    return result;
}

std::vector<PlstItem> PgTablesRepository::getPlstTableFromRes(PGresult* pgRes)
{
    std::vector<PlstItem> result;

    for (int i = 0; i < PQntuples(pgRes); i++)
    {
        int i_num = PQfnumber(pgRes, "id");
        int n_num = PQfnumber(pgRes, "name");

        char* id = PQgetvalue(pgRes, i, i_num);
        char* name = PQgetvalue(pgRes, i, n_num);

        result.push_back(
            PlstItem(
                atoi(id),
                string(name)));
    }
    return result;
}
