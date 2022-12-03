#include "TestConfig.h"

shared_ptr<IConnect> testFac(const string& email, const string& password)
{
    return shared_ptr<IConnect>(new TestConnect(email, password));
}


map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)> TestConfig::getConnectionMap()
{
    return map<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>({ std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(USER_CONNECT, testFac),
         std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ADMIN_CONNECT, testFac) ,
         std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(ARTIST_CONNECT, testFac),
         std::pair<Role, shared_ptr<IConnect>(*)(const string& email, const string& password)>(USER_CONNECT, testFac) });
}
