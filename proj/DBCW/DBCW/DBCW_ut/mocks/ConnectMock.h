#pragma once

#include <memory>
#include "AlbumsRepositoryMock.h"
#include "MusRepositoryMock.h"
#include "PlaylistRepositoryMock.h"
#include "TablesRepositoryMock.h"
#include "ArtistRepositoryMock.h"
#include "GraphRepoMock.h"
#include "UserRepoMock.h"

#include "IConnect.h"

using namespace std;

class ConnectMock : public IConnect
{
public:
	virtual Repositories getRepos() 
	{
		return Repositories ( 
			make_shared<AlbumsRepositoryMock>(),
			make_shared<MusRepositoryMock>(),
			make_shared<PlaylistRepositoryMock>(),
			make_shared<TablesRepositoryMock>(),
			make_shared<ArtistRepositoryMock>(),
			make_shared<GraphRepoMock>(),
			make_shared<UserRepoMock>()
		);
	};

	virtual ~ConnectMock() = default;
};

