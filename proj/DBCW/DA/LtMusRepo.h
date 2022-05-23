#pragma once
#include "../DBCW/IMusRepository.h"
#include <sqlite3.h>
class LtMusRepo :
    public IMusRepository
{
private:
    sqlite3* conn;
public:
    LtMusRepo (sqlite3* _conn) : conn(_conn) {}
    virtual void update(const string& uId, int mId) override {}
    virtual vector<MusItem> getMusByName(const string& name) override {}
};

