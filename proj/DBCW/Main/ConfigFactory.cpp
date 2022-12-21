#include "ConfigFactory.h"

shared_ptr<Config> pgFactory()
{
	return make_shared<ConConfig>();
}

shared_ptr<Config> pgFactoryTest()
{
	return make_shared<TestConfig>();
}

ConfigFactory::ConfigFactory()
{
	mapa.insert({ "postgresql", pgFactory });
	mapa.insert({ "postgresql-test", pgFactoryTest });
}
