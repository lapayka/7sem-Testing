#pragma once
#include "../DBCW/IGraphRepo.h"
#include <sqlite3.h>
class LtGraphRepo :
    public IGraphRepo
{
private:
    sqlite3* conn;
public:
    LtGraphRepo(sqlite3* _conn) : conn(_conn) {}
    virtual std::vector<std::pair<int, int>> getGraph() override {}
};

