#include "View.h"

ostream& operator << (ostream& str, const PlstItem& item)
{
	str << item.name;

	return str;
}

ostream& operator << (ostream& str, const MusItem& item)
{
	str << item.name << " " << item.duration << " " << item.alName << " " << item.arName;

	return str;
}