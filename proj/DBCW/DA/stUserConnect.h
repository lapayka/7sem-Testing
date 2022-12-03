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
        string connParameters = "dbname = test user = postgres password = " + pass;
        connPtr = PQconnectdb(connParameters.c_str());

        if (PQstatus(connPtr) != CONNECTION_OK)
        {
            throw ConnectException(PQerrorMessage(connPtr));
        }

        std::string query("select * from users where email = '" + email + "';");
        PGresult* res = PQexec(connPtr, query.c_str());

        int tuples = PQntuples(res);

        PQclear(res);
        if (tuples == 0)
        {
            throw LoginException(PQerrorMessage(connPtr));
        }
    };

    virtual ~stUserConnect() = default;
};

