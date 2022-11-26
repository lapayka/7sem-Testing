#include "TestConnect.h"

Repositories TestConnect::getRepos()
{
    return Repositories(shared_ptr<IAlbumsRepository>(new PgAlbumRepository(connPtr)),
        shared_ptr<IMusRepository>(new PgMusRepository(connPtr)),
        shared_ptr<IPlaylistRepository>(new PgPlaylistRepository(connPtr)),
        shared_ptr<ITablesRepository>(new PgTablesRepository(connPtr)),
        shared_ptr<IArtistRepository>(new PgArtistRepository(connPtr)),
        shared_ptr<IGraphRepo>(new PgGraphRepository(connPtr)),
        shared_ptr<IUserRepo>(new PgUserRepo(connPtr)));
}
