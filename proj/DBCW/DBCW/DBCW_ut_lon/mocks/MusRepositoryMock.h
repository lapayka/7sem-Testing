#pragma once
#include <string>
#include <vector>
#include "MusItem.h"
using namespace std;

#include "IMusRepository.h"

class MusRepositoryMock : public IMusRepository
{
public:
	virtual void update(const string& uId, int mId) override {};
	virtual vector<MusItem> getMusByName(const string & name) override { return vector<MusItem>(); };
};

