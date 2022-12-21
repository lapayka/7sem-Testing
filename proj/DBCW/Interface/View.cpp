#include "View.h"

ostream& operator << (ostream& str, const PlstItem& item)
{
	str.width(30), str << item.name;

	return str;
}

ostream& operator << (ostream& str, const MusItem& item)
{
	str.width(20);
	str  << item.name, str.width(15), str << item.duration, str.width(30), str << item.alName, str.width(30), str << item.arName;

	return str;
}