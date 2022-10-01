#pragma once
#include "IGraphRepo.h"
#include "libpq-fe.h"
#include <string>
using namespace std;

class PgGraphRepository :
    public IGraphRepo
{
private:
    PGconn* conn;
public:
    PgGraphRepository(PGconn* _conn) : conn(_conn) {}
    virtual vector<std::pair<int, int>> getGraph() override
    {
        PGresult* res = PQexec(conn, "select id1, id2 from (select u1.id as id1, u2.id as id2, FN_FIND_CORRELATION(u1.email,  u2.email) as correlation from users u1 join users u2 on u1.email > u2.email) as tmp where tmp.correlation = 1;");

        std::vector<std::pair<int, int>> result(getPairs(res));

        PQclear(res);

        return result;
    };
private:
    vector<std::pair<int, int>> getPairs(PGresult * pgRes)
    {
        std::vector<std::pair<int, int>> result;

        for (int i = 0; i < PQntuples(pgRes); i++)
        {
            int i1_num = PQfnumber(pgRes, "id1");
            int i2_num = PQfnumber(pgRes, "id2");

            char* id1 = PQgetvalue(pgRes, i, i1_num);
            char* id2 = PQgetvalue(pgRes, i, i2_num);


            result.push_back(
                make_pair<int, int>(
                    stoi(id1),
                    stoi(id2)));
        }
        return result;
    }
};

