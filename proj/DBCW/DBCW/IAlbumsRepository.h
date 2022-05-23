#pragma once
#include "MusItem.h"
#include <vector>
#include <string>

class IAlbumsRepository
{
public:
	virtual void create(const std::vector<MusItem>& items, const std::string& name, const std::string& arId) = 0;
	virtual void alDelete(int id) = 0;
	virtual std::vector<int> getAlbumsByName(const std::string & name) = 0;
};

