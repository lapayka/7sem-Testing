#pragma once

#include "PlstItem.h"
#include "MusItem.h"
#include <vector>
#include <string>

using namespace std;

class IPlaylistRepository
{
public:
	virtual void create(const string &nam, const string& user) = 0;
	virtual void del(int id) = 0;
	virtual void aUpdate(const MusItem& item, int id) = 0;

	virtual void delCompFromPlst(int mid, int pid) = 0;

	virtual void setOrder(int id, const vector<int> & orders) = 0;
};

