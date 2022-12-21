#pragma once

#include <memory>
#include "IAlbumsRepository.h"
#include "IMusRepository.h"
#include "IPlaylistRepository.h"
#include "ITablesRepository.h"
#include "IArtistRepository.h"
#include "IGraphRepo.h"
#include "IUserRepo.h"

using namespace std;

struct Repositories
{
	Repositories() {}
	Repositories(shared_ptr<IAlbumsRepository> a, shared_ptr<IMusRepository> b, shared_ptr<IPlaylistRepository> c, shared_ptr<ITablesRepository> d, shared_ptr<IArtistRepository> e, shared_ptr<IGraphRepo> f, shared_ptr<IUserRepo> u)
		: albRepPtr(a),
		  musRepPtr(b),
		  plstRepPtr(c),
		  tabRepPtr(d),
		  artRepPtr(e),
		  grRepo(f),
		  usRepo(u)
	{}



	shared_ptr<IAlbumsRepository> albRepPtr;
	shared_ptr<IMusRepository> musRepPtr;
	shared_ptr<IPlaylistRepository> plstRepPtr;
	shared_ptr<ITablesRepository> tabRepPtr;
	shared_ptr<IArtistRepository> artRepPtr;
	shared_ptr<IGraphRepo> grRepo;
	shared_ptr<IUserRepo> usRepo;
};

enum Role { USER_CONNECT, ADMIN_CONNECT, ARTIST_CONNECT};

class IConnect
{
public:

	virtual Repositories getRepos() = 0;

	virtual ~IConnect() = default;
};

