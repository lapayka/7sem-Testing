#pragma once

#include <exception>
#include <string>
#include "DBStartException.h"

using namespace std;
class ConnectException : public std::exception
{
private:
	string str;
public:
	ConnectException(const string& _str) : str(_str) {}
	virtual char const* what() const override { return str.c_str(); };
};

