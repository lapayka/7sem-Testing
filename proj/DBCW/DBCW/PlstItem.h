#pragma once
#include <string>

using namespace std;
class PlstItem
{
public:
	PlstItem(int _id, const string& str) :
		id(_id),
		name(str)
	{

	}
	int id;
	std::string name;
};

