#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "Facade.h"
#include "mocks/ConnectMock.h"
#include "mocks/ConfigMock.h"

BOOST_AUTO_TEST_SUITE(FacadeTS)

BOOST_AUTO_TEST_CASE(BLTablesGetMusicByAlbumTest) //
{
	shared_ptr<ConfigMock> cm = make_shared<ConfigMock>();

	Facade facade(cm, "", "", ADMIN_CONNECT);

	vector<MusItem> res(facade.getMusicByAlbum("vga11"));

	BOOST_CHECK_EQUAL(res[0].name, "vgm312");
	BOOST_CHECK_EQUAL(res[1].name, "vgm313");
	BOOST_CHECK_EQUAL(res[2].name, "vgm311");
}


BOOST_AUTO_TEST_CASE(BLTablesGetMusicByArtistTest)//
{
	shared_ptr<ConfigMock> cm = make_shared<ConfigMock>();

	Facade facade(cm, "", "", ADMIN_CONNECT);

	vector<MusItem> res(facade.getMusicByArtist("abc123@mail.ru"));

	BOOST_CHECK_EQUAL(res[0].name, "vgm321");
	BOOST_CHECK_EQUAL(res[1].name, "vgm322");
	BOOST_CHECK_EQUAL(res[2].name, "vgm323");
	

	BOOST_CHECK_EQUAL(res[3].name, "vgm411");
	BOOST_CHECK_EQUAL(res[4].name, "vgm412");
	BOOST_CHECK_EQUAL(res[5].name, "vgm413");
}


BOOST_AUTO_TEST_SUITE_END()
