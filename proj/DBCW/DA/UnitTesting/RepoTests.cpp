#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "TestConnect.h"
#include "TestConfig.h"
#include "DBCW/Facade.h"

BOOST_AUTO_TEST_SUITE(PgAlbum)


BOOST_AUTO_TEST_CASE(PgAlbumGetByNameTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	vector<int> res(repos.albRepPtr->getAlbumsByName("vga11"));

	BOOST_CHECK_EQUAL(res[0], 1);
	BOOST_CHECK_EQUAL(res[1], 4);
}


BOOST_AUTO_TEST_CASE(PgAlbumCreateTestPlusDelete)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	repos.albRepPtr->create({ MusItem(0, "testmus1", "5:40", "testalbum", "abc1Q@mail.ru"),
							  MusItem(0, "testmus2", "3:40", "testalbum", "abc1Q@mail.ru"), 
							  MusItem(0, "testmus3", "4:40", "testalbum", "abc1Q@mail.ru"),
		}, "testalbum", "abc1@mail.ru");

	vector<int> res(repos.albRepPtr->getAlbumsByName("testalbum"));

	BOOST_TEST(res[0] > 8);

	repos.albRepPtr->alDelete(res[0]);

	res = repos.albRepPtr->getAlbumsByName("testalbum");

	BOOST_CHECK_EQUAL(res.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgArtist)


BOOST_AUTO_TEST_CASE(PgArtistsGetByNameTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	vector<string> res(repos.artRepPtr->getArtistsByName("vgg"));

	BOOST_CHECK_EQUAL(res[0], "abc1@mail.ru");

}





BOOST_AUTO_TEST_CASE(PgArtistsCreateTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());
	
	repos.artRepPtr->createArtist("testEmail@mail.ru", "123", "CreateTestArtist");


	vector<string> res(repos.artRepPtr->getArtistsByName("CreateTestArtist"));

	BOOST_CHECK_EQUAL(res[0], "testEmail@mail.ru");

}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgMusics)



BOOST_AUTO_TEST_CASE(PgMusicsCreateTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	repos.musRepPtr->update("abc1@mail.ru", 7);

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgMusics)


BOOST_AUTO_TEST_CASE(PgTablesGetMusicByAlbumTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	vector<MusItem> res(repos.tabRepPtr->getMusByAlbum(6));

	BOOST_CHECK_EQUAL(res[0].name, "vgm322");
	BOOST_CHECK_EQUAL(res[1].name, "vgm323");
	BOOST_CHECK_EQUAL(res[2].name, "vgm321");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgTables)


BOOST_AUTO_TEST_CASE(PgTablesGetMusicByArtistTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	vector<MusItem> res(repos.tabRepPtr->getMusByArtist("abc123@mail.ru"));
	

	BOOST_CHECK_EQUAL(res[0].name, "vgm322");
	BOOST_CHECK_EQUAL(res[1].name, "vgm323");
	BOOST_CHECK_EQUAL(res[2].name, "vgm411");
								 
	BOOST_CHECK_EQUAL(res[3].name, "vgm413");
	BOOST_CHECK_EQUAL(res[4].name, "vgm321");
	BOOST_CHECK_EQUAL(res[5].name, "vgm412");
}


BOOST_AUTO_TEST_CASE(PgTablesGetPlaylistsByUserTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	vector<PlstItem> res(repos.tabRepPtr->getPlaylistsByUser("abc123@mail.ru"));

	BOOST_CHECK_EQUAL(res[0].name, "vgp3");
	BOOST_CHECK_EQUAL(res[1].name, "vgp11");
}


BOOST_AUTO_TEST_CASE(PgTablesGetMusicByPlaylistTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	vector<MusItem> res(repos.tabRepPtr->getMusByPlaylist(6));

	BOOST_CHECK_EQUAL(res[0].name, "vgm322");
	BOOST_CHECK_EQUAL(res[1].name, "vgm123");
	BOOST_CHECK_EQUAL(res[2].name, "vgm111");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgPlaylists)


BOOST_AUTO_TEST_CASE(PgPlaylistsTest)
{
	TestConnect conn("", "");

	Repositories repos(conn.getRepos());

	repos.plstRepPtr->create("testPlst", "abc123@mail.ru");

	vector<PlstItem> res(repos.tabRepPtr->getPlaylistsByUser("abc123@mail.ru"));

	int i = 0;

	for (i = 0; i < res.size() && res[i].name != "testPlst"; i++)
		;

	repos.plstRepPtr->aUpdate(MusItem(1, "", "", "", ""), res[i].id);
	repos.plstRepPtr->aUpdate(MusItem(2, "", "", "", ""), res[i].id);
	vector<MusItem> mres(repos.tabRepPtr->getMusByPlaylist(res[i].id));

	BOOST_CHECK_EQUAL(mres[0].id, 1);
	BOOST_CHECK_EQUAL(mres[1].id, 2);

	repos.plstRepPtr->del(res[i].id);

	vector<MusItem> dres(repos.tabRepPtr->getMusByPlaylist(res[i].id));

	BOOST_TEST(dres.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
