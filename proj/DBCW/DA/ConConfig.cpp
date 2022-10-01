#include "ConConfig.h"
shared_ptr<IConnect> adminFactory(const string& email, const string& password)
{
	return shared_ptr<IConnect>(new AdminConnect(email, password));
}

shared_ptr<IConnect> artistFactory(const string& email, const string& password)
{
	return shared_ptr<IConnect>(new ArtistConnect(email, password));
}

shared_ptr<IConnect> userFactory(const string& email, const string& password)
{
	return shared_ptr<IConnect>(new stUserConnect(email, password));
}

ConConfig::ConConfig()
{
	mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(USER_CONNECT, userFactory));
	mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ARTIST_CONNECT, artistFactory));
	mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ADMIN_CONNECT, adminFactory));
}



map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> ConConfig::getConnectionMap()
{
	return mapa;
}
