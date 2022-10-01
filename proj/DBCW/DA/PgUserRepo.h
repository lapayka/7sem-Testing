#pragma once
#include "IUserRepo.h"
#include "libpq-fe.h"

class PgUserRepo :
    public IUserRepo
{
private:
    PGconn* connPtr;

public:
    PgUserRepo(PGconn* _connPtr) : connPtr(_connPtr) {}

    virtual std::pair<std::string, std::string> UserInfo(const std::string& id) override
    {
        std::string query("select * from Users where email = '" + id + "';");

        PGresult* res = PQexec(connPtr, query.c_str());


        int e_num = PQfnumber(res, "email");
        int p_num = PQfnumber(res, "password");
        
        char* pid = PQgetvalue(res, 0, e_num);
        char* pass = PQgetvalue(res, 0, p_num);
        std::pair<std::string, std::string> result(std::make_pair<std::string, std::string>(std::string(pid), std::string(pass)));
        
        PQclear(res);

        return result;
    }

    virtual bool login(const string& email, const string& password) override
    {
        std::string query("select * from Users where email = '" + email + "';");

        PGresult* res = PQexec(connPtr, query.c_str());

        if (PQntuples(res))
        {
            PQclear(res);
            return false;
        }
        PQclear(res);
        {
            std::string query("insert into users(email, password) values('" + email + "', '" + password + "');");
            PGresult* res = PQexec(connPtr, query.c_str());
            PQclear(res);
        }
        
        return true;
    }
};

