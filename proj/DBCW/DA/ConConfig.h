#pragma once
#include "Config.h"
#include "AdminConnect.h"
#include "stUserConnect.h"
#include "ArtistConnect.h"

using namespace std;
class ConConfig : public Config
{
protected:
	map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> mapa;

public:
	ConConfig();
	virtual map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> getConnectionMap() override;
};

