#pragma once

#include "Config.h"
#include "../TestConnect.h"

class ConfigMock : public Config
{
    virtual map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> getConnectionMap() override;
};