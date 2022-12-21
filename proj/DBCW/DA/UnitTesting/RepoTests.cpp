#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "TestConnect.h"
#include "TestConfig.h"
#include "Facade.h"
#include "ObjectMother.h"

ObjectMother mother;

BOOST_AUTO_TEST_SUITE(PgAlbum)


BOOST_AUTO_TEST_CASE(PgAlbumGetByNameTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	vector<int> res(repos.albRepPtr->getAlbumsByName(mother.GetAlbumName(1, 1)));
	
	BOOST_CHECK_EQUAL(res[0], 1);
	BOOST_CHECK_EQUAL(res[1], 4);
}


BOOST_AUTO_TEST_CASE(PgAlbumCreateTestPlusDelete)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	repos.albRepPtr->create({ mother.GetDefaultMusItemByDuration("5:40"),
							  mother.GetDefaultMusItemByDuration("3:40"),
							  mother.GetDefaultMusItemByDuration("4:40")
		}, mother.GetDefaultAlbumName(), mother.GetEmailByName("abc1"));
	
	vector<int> res(repos.albRepPtr->getAlbumsByName(mother.GetDefaultAlbumName()));
	
	BOOST_TEST(res[0] > 8);
	
	repos.albRepPtr->alDelete(res[0]);
	
	res = repos.albRepPtr->getAlbumsByName(mother.GetDefaultAlbumName());
	
	BOOST_CHECK_EQUAL(res.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgArtist)


BOOST_AUTO_TEST_CASE(PgArtistsGetByNameTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	vector<string> res(repos.artRepPtr->getArtistsByName("vgg"));
	
	BOOST_CHECK_EQUAL(res[0], mother.GetEmailByName("abc1"));

}





BOOST_AUTO_TEST_CASE(PgArtistsCreateTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	repos.artRepPtr->createArtist(mother.GetEmailByName("testEmail"), "123", mother.GetDefaultArtistName());
	
	
	vector<string> res(repos.artRepPtr->getArtistsByName(mother.GetDefaultArtistName()));
	
	BOOST_CHECK_EQUAL(res[0], mother.GetEmailByName("testEmail"));

}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgMusics)



BOOST_AUTO_TEST_CASE(PgMusicsCreateTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	repos.musRepPtr->update(mother.GetEmailByName("abc1"), 7);
	
	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgMusics)


BOOST_AUTO_TEST_CASE(PgTablesGetMusicByAlbumTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	vector<MusItem> res(repos.tabRepPtr->getMusByAlbum(6));
	
	BOOST_CHECK_EQUAL(res[0].name, mother.GetMusName(3, 2, 2));
	BOOST_CHECK_EQUAL(res[1].name, mother.GetMusName(3, 2, 3));
	BOOST_CHECK_EQUAL(res[2].name, mother.GetMusName(3, 2, 1));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgTables)


BOOST_AUTO_TEST_CASE(PgTablesGetMusicByArtistTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	vector<MusItem> res(repos.tabRepPtr->getMusByArtist(mother.GetEmailByName("abc123")));
	
	
	BOOST_CHECK_EQUAL(res[0].name, mother.GetMusName(3, 2, 2));
	BOOST_CHECK_EQUAL(res[1].name, mother.GetMusName(3, 2, 3));
	BOOST_CHECK_EQUAL(res[2].name, mother.GetMusName(4, 1, 1));
															 
	BOOST_CHECK_EQUAL(res[3].name, mother.GetMusName(4, 1, 3));
	BOOST_CHECK_EQUAL(res[4].name, mother.GetMusName(3, 2, 1));
	BOOST_CHECK_EQUAL(res[5].name, mother.GetMusName(4, 1, 2));
}


BOOST_AUTO_TEST_CASE(PgTablesGetPlaylistsByUserTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	vector<PlstItem> res(repos.tabRepPtr->getPlaylistsByUser(mother.GetEmailByName("abc123")));
	
	BOOST_CHECK_EQUAL(res[0].name, mother.GetPlstName(3));
	BOOST_CHECK_EQUAL(res[1].name, mother.GetPlstName(11));
}


BOOST_AUTO_TEST_CASE(PgTablesGetMusicByPlaylistTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	vector<MusItem> res(repos.tabRepPtr->getMusByPlaylist(6));
	
	BOOST_CHECK_EQUAL(res[0].name, mother.GetMusName(3, 2, 2));
	BOOST_CHECK_EQUAL(res[1].name, mother.GetMusName(1, 2, 3));
	BOOST_CHECK_EQUAL(res[2].name, mother.GetMusName(1, 1, 1));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(PgPlaylists)


BOOST_AUTO_TEST_CASE(PgPlaylistsTest)
{
	TestConnect conn("", "");
	
	Repositories repos(conn.getRepos());
	
	repos.plstRepPtr->create(mother.GetDefaultPlstName(), mother.GetEmailByName("abc123"));

	vector<PlstItem> res(repos.tabRepPtr->getPlaylistsByUser(mother.GetEmailByName("abc123")));
	
	int i = 0;
	
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
