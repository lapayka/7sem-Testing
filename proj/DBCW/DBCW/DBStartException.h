#pragma once

#include <exception>
#include <string>

using namespace std;
class DBStartException : public std::exception
{

public:

	virtual char const* what() const = 0;
};

