#pragma once

#include <vector>

#include "IGraphRepo.h"

class GraphRepoMock : public IGraphRepo
{
public:
	virtual std::vector<std::pair<int, int>> getGraph() override { return std::vector<std::pair<int, int>>(); };
};

