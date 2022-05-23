#pragma once
#include "IPgConnect.h"

#include "ConnectException.h"

class AdminConnect :
    public IPgConnect
{
public:
    AdminConnect(const string& email, const string& pass)
    {
        string query("dbname = postgres user = postgres password = " + pass);
        connPtr = PQconnectdb(query.c_str());

        if (PQstatus(connPtr) != CONNECTION_OK)
        {
            throw ConnectException(PQerrorMessage(connPtr));
        }
    };

    virtual ~AdminConnect() = default;
};

