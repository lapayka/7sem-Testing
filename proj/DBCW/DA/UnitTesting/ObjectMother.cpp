#include "ObjectMother.h"

std::string ObjectMother::GetArtistName(int id)
{
	return "vgg" + std::to_string(id);
}

std::string ObjectMother::GetAlbumName(int arid, int alid)
{
	return "vga" + std::to_string(arid) + std::to_string(alid);
}

std::string ObjectMother::GetMusName(int arid, int alid, int musid)
{
	return "vgm" + std::to_string(arid) + std::to_string(alid) + std::to_string(musid);;
}

std::string ObjectMother::GetPlstName(int plstid)
{
	return "vgp" + std::to_string(plstid);
}

std::string ObjectMother::GetEmailByName(const std::string& name)
{
	return name + "@mail.ru";
}

std::string ObjectMother::GetDefaultArtistName()
{
	return std::string("CreateTestArtist");
}

std::string ObjectMother::GetDefaultAlbumName()
{
	return std::string("testalbum");
}

std::string ObjectMother::GetDefaultPlstName()
{
	return "testPlst";
}

MusItem ObjectMother::GetDefaultMusItemByDuration(const std::string& duration)
{
	return MusItem(0, "testmus1", duration, "testalbum", "abc1Q@mail.ru");
}
