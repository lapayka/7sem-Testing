#pragma once

#include "PlstItem.h"
#include "MusItem.h"
#include <vector>
#include <string>

using namespace std;

#include "IPlaylistRepository.h"

class PlaylistRepositoryMock : public IPlaylistRepository
{
public:
	virtual void create(const string &nam, const string& user) override {};
	virtual void del(int id) override {};
	virtual void aUpdate(const MusItem& item, int id) override {};

	virtual void delCompFromPlst(int mid, int pid) override {};

	virtual void setOrder(int id, const vector<int> & orders) override {};
};

