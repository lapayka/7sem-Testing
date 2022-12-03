#pragma once
#include "LoginException.h"
#include "IPgConnect.h"
class ArtistConnect :
    public IPgConnect
{
public:
    ArtistConnect(const string& email, const string& pass)
    {
        string connParameters = "dbname = test user = postgres password = " + pass;
        connPtr = PQconnectdb(connParameters.c_str());

        if (PQstatus(connPtr) != CONNECTION_OK)
        {
            throw ConnectException(PQerrorMessage(connPtr));
        }

        std::string query("select * from artists where email = '" + email + "' and password = '" + pass + "';");
        PGresult* res = PQexec(connPtr, query.c_str());

        int tuples = PQntuples(res);

        PQclear(res);
        if (tuples == 0)
        {
            throw LoginException(PQerrorMessage(connPtr));
        }
    };

    virtual ~ArtistConnect() = default;
};

