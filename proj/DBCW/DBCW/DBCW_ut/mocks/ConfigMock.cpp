#include "ConfigMock.h"

shared_ptr<IConnect> factoryMock(const string& email, const string& password)
{
    shared_ptr<IConnect> tmp = make_shared<ConnectMock>();
    return tmp;
}

map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> ConfigMock::getConnectionMap()
{
    map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> mapa;
    mapa.insert(std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ADMIN_CONNECT, factoryMock));
    return mapa;
}