#pragma once
#include "IPgConnect.h"
class TestConnect :
    public IPgConnect
{

public:

    TestConnect(const string& email, const string& pass)
    {
        string query("dbname = test user = postgres password = 4Nikarulez_7");
        connPtr = PQconnectdb(query.c_str());

        if (PQstatus(connPtr) != CONNECTION_OK)
        {
            fprintf(stdout, "%s", PQerrorMessage(connPtr));
            //throw
        }
    };

    virtual ~TestConnect() = default;
};

