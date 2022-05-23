#pragma once

#include <vector>
class IGraphRepo
{
public:
	virtual std::vector<std::pair<int, int>> getGraph() = 0;
};

