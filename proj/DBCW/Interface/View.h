#pragma once
#include "MusItem.h"
#include "PlstItem.h"

#include <vector>
#include <iostream>

using namespace std;


ostream& operator << (ostream& str, const PlstItem& item);


ostream& operator << (ostream& str, const MusItem& item);

class View
{
public:
	void outputPlaylists(const vector<PlstItem>& items)
	{
		int i = 0;

		std::cout << "Id   Name\n";

		for (const auto& item : items)
		{
			cout.setf(ios::left);
			cout.width(5);
			std::cout << ++i << item << "\n";
		}

		std::cout << std::endl;
	}

	void outputMusics(const vector<MusItem>& items)
	{
		int i = 0;
		
		std::cout << "Id   Name              Duration        Album                        Artist\n";

		for (const auto& item : items)
		{
			cout.setf(ios::left);
			cout.width(5);
			std::cout <<  ++i << " " << item << "\n";
		}

		std::cout << std::endl;
	}
};

