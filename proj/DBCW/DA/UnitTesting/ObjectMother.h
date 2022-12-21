#pragma once

#include <string>
#include "MusItem.h"

class ObjectMother
{
public:
	std::string GetArtistName(int id);
	std::string GetAlbumName(int arid, int alid);
	std::string GetMusName(int arid, int alid, int musid);
	std::string GetPlstName(int plstid);

	std::string GetEmailByName(const std::string& name);

	std::string GetDefaultArtistName();
	std::string GetDefaultAlbumName();
	std::string GetDefaultPlstName();

	MusItem GetDefaultMusItemByDuration(const std::string &duration);
};

