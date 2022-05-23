#pragma once
#include "LoginException.h"
#include "IPgConnect.h"
class ArtistConnect :
    public IPgConnect
{
public:
    ArtistConnect(const string& email, const string& pass)
    {
        char connParameters[] = "dbname = postgres user = artist password = artist";
        connPtr = PQconnectdb(connParameters);

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
            PQclear(res);
            throw LoginException(PQerrorMessage(connPtr));
        }
    };

    virtual ~ArtistConnect() = default;
};

