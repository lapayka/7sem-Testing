#pragma once
#include "IPlaylistRepository.h"
#include "libpq-fe.h"
class PgPlaylistRepository :
    public IPlaylistRepository
{
private:
	PGconn* connPtr;
public:
	PgPlaylistRepository(PGconn* _connPtr) : connPtr(_connPtr) {}
	virtual void create(const string& name, const string& user) override;
	virtual void del(int id) override;
	virtual void aUpdate(const MusItem& item, int id) override;
};

