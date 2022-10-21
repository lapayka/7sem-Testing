#pragma once

#include <exception>
#include <string>
#include "DBStartException.h"

using namespace std;
class LoginException : public std::exception
{
private:
	string str;
public:
	LoginException(const string& _str) : str(_str) {}
	virtual char const* what() const noexcept override { return str.c_str(); }
};

