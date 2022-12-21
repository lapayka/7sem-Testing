#pragma once
#include <vector>
#include "MusItem.h"
#include <string>
#include "PlstItem.h"

#include "ITablesRepository.h"

class TablesRepositoryMock : public ITablesRepository
{
public:
	virtual std::vector<MusItem> getMusByArtist(const string &id) override
	{
		if (id == "vga3")
			return std::vector<MusItem>({MusItem(0, "vgm321", "", "", ""), MusItem(0, "vgm322", "", "", ""), MusItem(0, "vgm323", "", "", "")}); 
		if (id == "vga4")
			return std::vector<MusItem>({MusItem(0, "vgm411", "", "", ""), MusItem(0, "vgm412", "", "", ""), MusItem(0, "vgm413", "", "", "")}); 
	}
	virtual std::vector<MusItem> getMusByAlbum(int id) override 
	{
		if (id == 5)
			return std::vector<MusItem>({MusItem(0, "vgm312", "", "", "")});

		if (id == 6)
			return std::vector<MusItem>({MusItem(0, "vgm313", "", "", ""), MusItem(0, "vgm311", "", "", "")});
	};
	virtual std::vector<MusItem> getMusByPlaylist(int id) override {return std::vector<MusItem>(); };
	virtual std::vector<PlstItem> getPlaylistsByUser(const string& id) override {return std::vector<PlstItem>(); };

};

