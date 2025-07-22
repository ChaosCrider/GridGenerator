#pragma once
#include <vector>

class UnionFinder {
private:
	std::vector<int> m_parent;
	std::vector<int> m_rank;
public:
	UnionFinder(int size);
	int find(int x);
	bool unionSets(int x, int y);
	bool connected(int x, int y);
};