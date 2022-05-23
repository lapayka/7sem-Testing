#pragma once
#include "MusItem.h"

#include <vector>

class IArtistRepository
{
public:
	virtual void createRequest(const string& UsId, const string& name) = 0;
	virtual vector<pair<string, string>> getAllRequests() = 0;
	virtual std::vector<std::string> getArtistsByName(const std::string& name) = 0;
	virtual void createArtist(const std::string & email, const std::string &password, const std::string &name) = 0;
};

