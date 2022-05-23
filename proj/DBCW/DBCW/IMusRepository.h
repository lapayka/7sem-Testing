#pragma once
#include <string>
#include <vector>
#include "MusItem.h"
using namespace std;

class IMusRepository
{
public:
	virtual void update(const string& uId, int mId) = 0;
	virtual vector<MusItem> getMusByName(const string & name) = 0;
};

