#pragma once
#include <vector>
#include <string>
using namespace std;

class IUserRepo
{
public:
	virtual std::pair<std::string, std::string> UserInfo(const std::string& id) = 0;

	virtual bool login(const string& email, const string& password) = 0;
};

