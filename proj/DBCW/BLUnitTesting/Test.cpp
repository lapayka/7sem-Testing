#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "../UnitTesting/TestConfig.h"
#include "../DBCW/Facade.h"

BOOST_AUTO_TEST_CASE(GetMusicByAlbumNameTest)
{
	TestConfig conf;


	Facade fac(conf, string(""), string(""), USER_CONNECT);
	vector<MusItem> res = fac.getMusicByAlbum("vga21");


	BOOST_TEST(res[0].name == "vgm311");
	BOOST_TEST(res[1].name == "vgm312");
	BOOST_TEST(res[2].name == "vgm313");
}

BOOST_AUTO_TEST_CASE(GetMusicByArtistNameTest)
{
	TestConfig conf;


	Facade fac(conf, string(""), string(""), USER_CONNECT);
	vector<MusItem> res = fac.getMusicByArtist("vgg2");

	BOOST_TEST(res[0].name == "vgm211");
	BOOST_TEST(res[1].name == "vgm212");
	BOOST_TEST(res[2].name == "vgm213");
	BOOST_TEST(res[3].name == "vgm311");
	BOOST_TEST(res[4].name == "vgm312");
	BOOST_TEST(res[5].name == "vgm313");
}