#pragma once

#include "BaseInterface.h"
#include "Config.h"
#include "ServerSettings.h"
#include "ServerController.h"

#include <memory>
#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/AsyncController.hpp"
#include <iostream>
using namespace std;

class WebWrapper :  public BaseInterface
{
private:
    shared_ptr<Config> config;
public:
    WebWrapper (shared_ptr<Config> conf)  : config(conf) {}

    virtual void work();
};