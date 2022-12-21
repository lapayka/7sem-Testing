#include "LiteConfig.h"

shared_ptr<IConnect> liteFactory(const string& email, const string& password)
{
	return make_shared<LiteConnect>(email, password);
}

LiteConfig::LiteConfig()
{
	mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(USER_CONNECT, liteFactory));
	mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ARTIST_CONNECT, liteFactory));
	mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ADMIN_CONNECT, liteFactory));
}
