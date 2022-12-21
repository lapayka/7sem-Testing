#pragma once
#include "MusItem.h"
#include <vector>
#include <string>

#include "IAlbumsRepository.h"

class AlbumsRepositoryMock : public IAlbumsRepository
{
public:
	virtual void create(const std::vector<MusItem>& items, const std::string& name, const std::string& arId) override {}
	virtual void alDelete(int id) override {}
	virtual std::vector<int> getAlbumsByName(const std::string & name) 
	{ 	
		if (name == "vga11")
			return std::vector<int> ({5, 6}); 
	}

	virtual ~AlbumsRepositoryMock() = default;
};

