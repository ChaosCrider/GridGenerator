#include "EndPointFinder.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>

/*

	* EndPointFinder.cpp

	* This file contains the implementation of the EndPointFinder class, which is responsible for finding end points in a tree structure represented by corridors.
	* The end points are defined as leaf nodes in the tree, and the class provides methods to find these end points and their corresponding corridors.

	* The findEndPoints method uses a priority queue to traverse the tree and identify corridors that connect leaf nodes to their neighbours.
	* The findLeaves method identifies all leaf nodes in the tree, which are nodes with only one connection.
	* The findNeighbours method retrieves all neighbours of a given node in the tree.
	* The class uses a map to keep track of the length of corridors from the starting leaf node to each node in the tree.
	* The end points are returned as a vector of corridors, each representing a connection between a leaf node and its neighbour with the total length of the corridor.
	* The class is designed to be used in scenarios where a tree structure needs to be analyzed to find end points, such as in pathfinding algorithms or network analysis.
	* The implementation is efficient and leverages standard library features such as vectors and maps for optimal performance.

	* return's a vector of corridors that represent the end points in the tree with their total distance length.

*/

std::vector<corridor> EndPointFinder::findEndPoints(const std::vector<corridor>& tree)
{

	std::vector<corridor> endPoints;
	std::vector<int> leafNodes = findLeaves(tree);
	std::vector<int> priorityQueue;
	// int roomId, int Length to starting leaf node
	std::map<int, int> calculatedTree;
	std::vector<corridor> candidates;

	for (int leaf : leafNodes) {

		std::cout << "Processing leaf node: " << leaf << std::endl;

		//initalize calculated tree with the current leaf node
		calculatedTree.clear();
		calculatedTree = { {leaf,0} };

		for (const auto& path : calculatedTree) {
			std::cout << "Id : " << path.first << ", length : " << path.second << std::endl;
		}
		std::cout << std::endl;

		// initialize the priority queue with the current leaf node
		priorityQueue.clear();
		priorityQueue.push_back(leaf);

		// keep processing until the priority queue is empty, and all nodes are processed.
		while (priorityQueue.size() > 0) {

			std::cout << " ******* ";

			// update priority Queue
			int currentNode = *priorityQueue.begin();
			priorityQueue.erase(priorityQueue.begin());

			// 
			//
			//
			// => todo: nodes are being processed out of order.
			// make sure that the nodes are being procesessed in the correct order.
			// 3rd iteratino can process a unprocessed node to another unprocessed node.
			//
			//
			//
			
			std::vector<int> processed{};

			// find all neighbours of the current node
			std::vector<int> neighbours = findNeighbours(currentNode, tree);

			std::cout << std::endl;
			std::cout << "Current Node: " << currentNode << ", Neighbours found: ";\
			for (const auto& neighbour : neighbours) {
				std::cout << neighbour << ", ";
			}
			std::cout << std::endl;


			// if the node only has one neighbour, add it to the candidates
			if (neighbours.size() == 1) {
				// find the corridor that connects the current node and the neighbour
				for (const auto& corridor : tree) {
					if ((corridor.startRoom == currentNode && corridor.endRoom == neighbours[0]) // 
						||
						(corridor.endRoom == currentNode && corridor.startRoom == neighbours[0])) // if the corridor connects the current node and the neighbour
					{

						if (calculatedTree.find(neighbours[0]) == calculatedTree.end()) {
							// if the neighbour is not already in the calculated tree, add it to the priority queue
							priorityQueue.push_back(neighbours[0]); // add the neighbour to the priority queue

						// * is this inverted somehow?
						// Create a path with the current node and the neighbour with the full length to starting leaf node
						std::cout << "Adding corridor from currentNode(_ " << currentNode << " _) to neighbours[0](_ " << neighbours[0] << " _) with length -> start length calculatedTree[currentNode](" << calculatedTree[currentNode] << ") and new length corridor.length(" << corridor.length << ") " << std::endl;
						std::cout << " => [neighbours[0]](_ " << neighbours[0] << " _) = calculatedTree[currentNode](" << calculatedTree[currentNode]  << ") + corridor.length("  << corridor.length << ")" << std::endl;
						calculatedTree[neighbours[0]] = calculatedTree[currentNode] + corridor.length;

						}


					}
				}
			}

			else {
			// iterate through all neighbours
				for (int neighbour : neighbours) {
					// iterate through all corridors in the tree to find the corridor that connects the current node and the neighbour
					for (const auto& corridor : tree) {
						//if the corridor connects the current node and the neighbour
						if ((corridor.startRoom == currentNode && corridor.endRoom == neighbour) ||
							(corridor.endRoom == currentNode && corridor.startRoom == neighbour)) {

							if ( calculatedTree.find(neighbour) == calculatedTree.end() ) {
								priorityQueue.push_back(neighbour); // add the neighbour to the priority queue

							// check if the endRoom is already visited
							if (calculatedTree.find(neighbour) == calculatedTree.end()) {
								// if not, create a path with the current neighbour and calculate the length from current path + corridor length
//								std::cout << "Adding corridor from " << currentNode << " to " << neighbour << " with length -> start length " << calculatedTree[currentNode] << " and new length " << corridor.length << std::endl;
								std::cout << "Adding corridor from currentNode(_ " << currentNode << " _) to neighbours[0](_ " << neighbours[0] << " _) with length -> start length {calculatedTree[currentNode](" << calculatedTree[currentNode] << ")} and new length {corridor.length(" << corridor.length << ")} " << std::endl;
								std::cout << " => [neighbours[0]](_ " << neighbours[0] << " _) = calculatedTree[currentNode](" << calculatedTree[currentNode] << ") + corridor.length(" << corridor.length << ")" << std::endl;

								calculatedTree[neighbour] = calculatedTree[currentNode] + corridor.length;
							


							}

} // end of if for neighbour not in priority queue
						} // end of if for corridor connection
					} // end of for loop for corridors
				} // end of for loop for neighbours
			} // end of if-else for neighbours.size()
		} // end of while loop

		std::cout << "Calculcated tree for leaf id " << leaf << " : " << std::endl;
		for (const auto& entry : calculatedTree) {
			std::cout << "Node: " << entry.first << ", Length: " << entry.second << std::endl;
		}
		std::cout << " " << std::endl;


		std::cout << "Finding longest path from leaf node: " << leaf << std::endl;
		corridor longestPath{0,0};

		for (const auto& entry : calculatedTree) {
			if (entry.second > longestPath.length && leaf != entry.first) {
				longestPath = { leaf, entry.first, entry.second };
			}
		}

		std::cout << "Selected : " << longestPath.startRoom << " to " << longestPath.endRoom << " with length " << longestPath.length << std::endl;
		std::cout << std::endl;

		candidates.push_back(longestPath);

	} // for leaf loop

    return candidates;
} // findEndPoints

std::vector<int> EndPointFinder::findLeaves(const std::vector<corridor>& tree)
{
	std::vector<int> leaves{};
	std::map<int, int> roomCorridorCount;

	for (const auto& corridor : tree) {
		roomCorridorCount[corridor.startRoom]++;
		roomCorridorCount[corridor.endRoom]++;
	}

	for (const auto& room : roomCorridorCount) {
		if (room.second == 1) { // Only one connection
			leaves.push_back(room.first);
		}
	}

	return leaves;
}

std::vector<int> EndPointFinder::findNeighbours(int node, const std::vector<corridor>& tree)
{
	// roomId
	std::vector<int> neighbours{};

	// Iterate through the corridors to find all neighbours of the given node
	for (const auto& corridor : tree) {
		// Check if the corridor starts or ends at the given node
		if (corridor.startRoom == node) {
			// If the corridor starts at the node, check if the endRoom is already in the neighbours
			if (std::find(neighbours.begin(), neighbours.end(), corridor.endRoom) == neighbours.end()) {
				// if the endRoom is not already in the neighbours, add it
				neighbours.push_back(corridor.endRoom);
			}
		}

		// Check if the corridor ends at the given node
		else if (corridor.endRoom == node) {
			// If the corridor ends at the node, check if the startRoom is already in the neighbours
			if (std::find(neighbours.begin(), neighbours.end(), corridor.endRoom) == neighbours.end()) {
				// if the startRoom is not already in the neighbours, add it
				neighbours.push_back(corridor.startRoom);
			}
		}
	}
	return neighbours;
}
