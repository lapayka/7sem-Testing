#pragma once

#include <map>

#include "AdminConnect.h"
#include "ArtistConnect.h"
#include "StUserConnect.h"

using namespace std;
class Config
{
protected:
	map<Role, shared_ptr<IConnect>(*)(const string &email, const string &password)> mapa;

public:
	Config() = default;
	virtual map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> getConnectionMap() = 0;
};

