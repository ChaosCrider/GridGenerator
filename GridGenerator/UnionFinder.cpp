#include "UnionFinder.h"
#include <iostream>

UnionFinder::UnionFinder(int size)
	: m_parent(size), m_rank(size, 0)
{
	for (int i = 0; i < size; ++i) {
		m_parent[i] = i; // Initialize each element to be its own parent
	}
}

int UnionFinder::find(int x) {
	/*
		 Find the root of the set containing x
		 If x is not its own parent, recursively find the parent
		 This implements path compression to flatten the structure
		 which helps in speeding up future queries
	*/
	//std::cout << "union find : find x = " << x << std::endl;
	if (m_parent[x] != x) {
		m_parent[x] = find(m_parent[x]); // Path compression
	}
	//std::cout << "parent x = " << m_parent[x] << std::endl;
	return m_parent[x];
}

bool UnionFinder::unionSets(int x, int y) {
	/*
		 Union two sets containing x and y
		 Find the roots of the sets containing x and y
		 If they are different, merge them
		 using union by rank to keep the tree flat
		 This helps in keeping the structure efficient
		 by always attaching the smaller tree under the larger tree
		 which reduces the height of the trees
	*/
	int rootX = find(x);
	int rootY = find(y);
	if (rootX == rootY) {
		return false; // They are already in the same set
	}
	if (m_rank[rootX] < m_rank[rootY]) {
		m_parent[rootX] = rootY; // Attach rootX under rootY
	}
	else if (m_rank[rootX] > m_rank[rootY]) {
		m_parent[rootY] = rootX; // Attach rootY under rootX
	}
	else {
		m_parent[rootY] = rootX; // Attach rootY under rootX
		m_rank[rootX]++; // Increase the rank of the new root
	}
	return true; // Successfully unioned the sets
}

bool UnionFinder::connected(int x, int y) {
	// Check if two elements are in the same set
	//std::cout << "union find : connected x = " << x << ", y = " << y << std::endl;
	return find(x) == find(y);
}
