#pragma once
#include "IConnect.h"
#include "libpq-fe.h"
#include <string>
#include "PgMusRepository.h"
#include "PgPlaylistRepository.h"
#include "PgTablesRepository.h"
#include "PgAlbumRepository.h"
#include "PgArtistRepository.h"
#include "PgGraphRepository.h"
#include "PgUserRepo.h"

using namespace std;
class IPgConnect :
    public IConnect
{
public:
    virtual Repositories getRepos() override 
    {
        return Repositories(shared_ptr<IAlbumsRepository>(new PgAlbumRepository(connPtr)),
                                shared_ptr<IMusRepository>(new PgMusRepository(connPtr)),
                                    shared_ptr<IPlaylistRepository>(new PgPlaylistRepository(connPtr)),
                                        shared_ptr<ITablesRepository>(new PgTablesRepository(connPtr)),
                                            shared_ptr<IArtistRepository>(new PgArtistRepository(connPtr)),
                                                shared_ptr<IGraphRepo>(new PgGraphRepository(connPtr)),
                                                    shared_ptr<IUserRepo>(new PgUserRepo(connPtr)));
    }
    virtual ~IPgConnect() { /*PQfinish(connPtr);*/ };
protected:
    PGconn * connPtr;
};

