#pragma once

#include <vector>
#include <utility>
#include "Coordinate.h"


class EndPointFinder
{
public:
	EndPointFinder() = default;
	~EndPointFinder() = default;

	std::vector<corridor> findEndPoints( const std::vector<corridor>& tree );

private:
	std::vector<int> findLeaves(const std::vector<corridor>& tree);
	std::vector<int> findNeighbours(int node, const std::vector<corridor>& tree);
	
};

