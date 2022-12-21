#include "ConfigFactory.h"

shared_ptr<Config> pgFactory()
{
	return make_shared<ConConfig>();
}

ConfigFactory::ConfigFactory()
{
	mapa.insert({ "postgresql", pgFactory });
}
