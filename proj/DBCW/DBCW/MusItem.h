#pragma once
#include <string>
#include <ctime>

using namespace std;

class MusItem
{
public:
	MusItem(int _id, const string &_name, const string &_duration, const string& _alName, const string& _arName, const string &_path)
		:
		id(_id),
		name(_name),
		duration(_duration),
		alName(_alName),
		arName(_arName),
		path(_path)
	{}

	MusItem(int _id, const string &_name, const string &_duration, const string& _alName, const string& _arName)
		:
		id(_id),
		name(_name),
		duration(_duration),
		alName(_alName),
		arName(_arName)
	{}

	int id;
	string name;
	string duration;
	string alName;
	string arName;
	string path;
};

