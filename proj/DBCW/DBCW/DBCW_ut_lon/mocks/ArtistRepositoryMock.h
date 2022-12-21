#pragma once
#include "MusItem.h"

#include <vector>

#include "IArtistRepository.h"

class ArtistRepositoryMock : public IArtistRepository
{
public:
	virtual void createRequest(const string& UsId, const string& name) override {}
	virtual vector<pair<string, string>> getAllRequests() override { return vector<pair<string, string>>(); }
	virtual std::vector<std::string> getArtistsByName(const std::string& name) override 
	{ 
		if ( name == "abc123@mail.ru")	
			return std::vector<std::string>({"vga3", "vga4"}); 
	}
	virtual void createArtist(const std::string & email, const std::string &password, const std::string &name) override {};
};

