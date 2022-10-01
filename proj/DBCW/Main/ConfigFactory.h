#pragma once

#include "ConConfig.h"

#include <fstream>

class ConfigFactory
{
private:
	map<string, shared_ptr<Config>(*)()> mapa;
public:
	ConfigFactory();

	shared_ptr<Config> create(const string& filename)
	{
		ifstream str(filename);
		string tmp;
		str >> tmp;
		return  mapa.at(tmp)();
	}
	
};

