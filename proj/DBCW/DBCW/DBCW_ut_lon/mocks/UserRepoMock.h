#pragma once
#include <vector>
#include <string>
using namespace std;

#include "IUserRepo.h"

class UserRepoMock : public IUserRepo
{
public:
	virtual std::pair<std::string, std::string> UserInfo(const std::string& id) override { return make_pair(std::string(), std::string()); };

	virtual bool login(const string& email, const string& password) override { return true; };
};

