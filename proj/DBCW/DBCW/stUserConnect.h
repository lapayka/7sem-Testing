#pragma once
#include "IPgConnect.h"

#include "../DBCW/LoginException.h"
#include "../DBCW/ConnectException.h"
class stUserConnect :
    public IPgConnect
{
public:
    stUserConnect(const string& email, const string& pass)
    {
        char connParameters[] = "dbname = postgres user = stock_user password = stock_user";
        connPtr = PQconnectdb(connParameters);

        if (PQstatus(connPtr) != CONNECTION_OK)
        {
            throw ConnectException(PQerrorMessage(connPtr));
        }

        std::string query("select * from users where email = '" + email + "' and password = '" + pass + "';");
        PGresult* res = PQexec(connPtr, query.c_str());

        int tuples = PQntuples(res);

        PQclear(res);
        if (tuples == 0)
        {
            PQclear(res);
            throw LoginException(PQerrorMessage(connPtr));
        }
    };

    virtual ~stUserConnect() = default;
};

