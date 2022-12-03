#pragma once
#include "ITablesRepository.h"
#include "libpq-fe.h"

class PgTablesRepository :
    public ITablesRepository
{
public:
	PgTablesRepository(PGconn* _connPtr) : connPtr(_connPtr) {}

	virtual std::vector<MusItem> getMusByArtist(const string& id) override;
	virtual std::vector<MusItem> getMusByAlbum(int id) override;
	virtual std::vector<MusItem> getMusByPlaylist(int id) override;
	virtual std::vector<PlstItem> getPlaylistsByUser(const string &id) override;

private:
	PGconn* connPtr;
	
private:
	std::vector<MusItem> getMusTableFromRes(PGresult* res);
	std::vector<PlstItem> getPlstTableFromRes(PGresult* res);
};

