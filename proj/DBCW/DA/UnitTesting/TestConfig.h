#pragma once
#include "DBCW/Config.h"
#include "TestConnect.h"

class TestConfig :
    public Config
{
public:
    virtual map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> getConnectionMap() override;
    
};

