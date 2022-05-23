#pragma once
#include "Config.h"
#include "../DBCW/AdminConnect.h"
#include "../DBCW/stUserConnect.h"
#include "../DBCW/ArtistConnect.h"

using namespace std;
class ConConfig : public Config
{
protected:
	map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> mapa;

public:
	ConConfig();
	virtual map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> getConnectionMap() override;
};

