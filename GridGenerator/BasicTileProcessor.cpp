#include <iostream>
#include <vector>
#include "BasicTileProcessor.h"
#include "ITileProcessor.h"
#include "eTileType.h"
#include "GridBlueprint.h"
#include "TileScanner.h"
#include "coordinate.h"

BasicTileProcessor::BasicTileProcessor()
    :m_blueprint(),
	m_grid(),
	m_tileScanner()
{}


std::vector<ETileType> BasicTileProcessor::generate(std::vector<ETileType>& grid, GridBlueprint& blueprint) {
	m_blueprint = blueprint;
	m_grid = grid;

	processWalls();
	processDoors();
	processFloors();

	return m_grid;
}


void BasicTileProcessor::processWalls() {
    /*
    	loop through the grid and check for floors.
		If a floor is found, check the surrounding tiles.
		identify empty tiles around the floor.
		evaluate every tile to identify what type of wall is needed.
    */

	std::vector<coordinate> scanRange = {
		coordinate(-1, -1), // Top-Left
		coordinate(0, -1),  // Top
		coordinate(1, -1),  // Top-Right
		coordinate(-1, 0),  // Left
		coordinate(1, 0),   // Right
		coordinate(-1, 1),  // Bottom-Left
		coordinate(0, 1),   // Bottom
		coordinate(1, 1)    // Bottom-Right
	};

	//for loop on the grid
    for (int y = 0; y < m_blueprint.m_gridHeight; ++y) {
        for (int x = 0; x < m_blueprint.m_gridWidth; ++x) {
            // check if the tile is a floor
			ETileType tileType = m_grid[coordinate(x, y).getIndex(m_blueprint)];
			if (tileType == getTileTypeFromLegend('c') || tileType == getTileTypeFromLegend('r')) {
			// cycle through all surounding tiles
				for (const auto & offset : scanRange) {
					int neighborX = x + offset.x;
					int neighborY = y + offset.y;
					// Get the index of the neighbor tile
					int index = coordinate(neighborX, neighborY).getIndex(m_blueprint);
					// If the tile is empty, process it
					if (m_grid[index] == getTileTypeFromLegend('x')) {
						// Scan for wall type
						std::cout << "Processing wall for tile at (" << neighborX << ", " << neighborY << ")\n";
						ETileType wallType = m_tileScanner.scanWallType(coordinate(neighborX, neighborY), m_grid, m_blueprint);
						m_grid[index] = wallType; // Write wall type to the grid
					}
				}
			}
        }
    }


	//process the surrounding tiles to determine wall type

	//write wall type to the grid

}


void BasicTileProcessor::processDoors() {

}


void BasicTileProcessor::processFloors() {

}


bool BasicTileProcessor::validate() {
    return true;
}