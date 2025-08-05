#include <iostream>
#include <vector>
#include "BasicTileProcessor.h"
#include "ITileProcessor.h"
#include "eTileType.h"
#include "GridBlueprint.h"
#include "TileScanner.h"
#include "coordinate.h"
#include "gridData.h"


BasicTileProcessor::BasicTileProcessor()
	: m_protoGridData(ProtoGridData(std::vector<ETileType>(), GridBlueprint()))
{};

BasicTileProcessor::BasicTileProcessor(ProtoGridData protoGridData)
	: m_protoGridData(protoGridData.m_grid, protoGridData.m_blueprint),
	m_tileScanner(),
	m_roomList()
{}

ProtoGridData BasicTileProcessor::generate(
	ProtoGridData protoGridData
) {
	m_protoGridData = protoGridData;

	processWalls();
	processDoors();
	processFloors();
	processEntryPoints();

	ProtoGridData tempGridData(m_protoGridData.m_grid, protoGridData.m_blueprint);
	tempGridData.m_roomList = m_protoGridData.m_roomList;
	tempGridData.entryPoints = m_protoGridData.entryPoints;


	return tempGridData;
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
   // Loop through each row in the grid
	for (int y = 0; y < m_protoGridData.m_blueprint.m_gridHeight; ++y) {
		// Loop through each column in the grid
		for (int x = 0; x < m_protoGridData.m_blueprint.m_gridWidth; ++x) {
			// Get the tile type at position (x, y)
			ETileType tileType = m_protoGridData.m_grid[coordinate(x, y).getIndex(m_protoGridData.m_blueprint)];

			// Check if the current tile is a floor tile of type 'c' or 'r'
			if (tileType == getTileTypeFromLegend('c') || tileType == getTileTypeFromLegend('r')) {
				// Loop through all offsets around the current tile (i.e., neighboring tiles)
				for (const auto& offset : scanRange) {
					int neighborX = x + offset.x;
					int neighborY = y + offset.y;

					// Get the index of the neighboring tile in the 1D grid array
					int index = coordinate(neighborX, neighborY).getIndex(m_protoGridData.m_blueprint);

					// Check if the neighboring tile is empty ('x' in the legend)
					if (m_protoGridData.m_grid[index] == getTileTypeFromLegend('x')) {
						// Determine the appropriate wall type based on surroundings
						ETileType wallType = m_tileScanner.scanWallType(
							coordinate(neighborX, neighborY),
							m_protoGridData.m_grid,
							m_protoGridData.m_blueprint
						);

						// Update the grid with the determined wall type
						m_protoGridData.m_grid[index] = wallType;
					}
				}
			}
		}
	}
}


void BasicTileProcessor::processDoors() {

	// Loop through the grid and check for corridor tiles.
	coordinate scanRange[] = {
		coordinate(-1, 0), // Left
		coordinate(1, 0),  // Right
		coordinate(0, -1), // Top
		coordinate(0, 1)   // Bottom
	};

	for (int x = 0; x < m_protoGridData.m_blueprint.m_gridWidth; x++) {
		for (int y = 0; y < m_protoGridData.m_blueprint.m_gridHeight; y++) {
			// check if the tile is a corridor tile
			if (m_protoGridData.m_grid[coordinate(x, y).getIndex(m_protoGridData.m_blueprint)] == getTileTypeFromLegend('c')) {
				// loop through the scan range
				for (const auto& offset : scanRange) {
					int neighborX = x + offset.x;
					int neighborY = y + offset.y;
					// Get the index of the neighbor tile
					int index = coordinate(neighborX, neighborY).getIndex(m_protoGridData.m_blueprint);
					// If the neighbor tile is a room floor, write door tile to the grid
					if (m_protoGridData.m_grid[index] == getTileTypeFromLegend('r')) {
						m_protoGridData.m_grid[coordinate(x, y).getIndex(m_protoGridData.m_blueprint)] = getTileTypeFromLegend('d'); // Write door tile
						break; // Exit loop after finding a room floor
					}
				}
			}
		}
	}
}


void BasicTileProcessor::processFloors() {
	TileScanner tileScanner = TileScanner();

	// Loop through the grid and check for room floor tiles.
	for (int x = 0; x < m_protoGridData.m_blueprint.m_gridWidth; x++) {
		for (int y = 0; y < m_protoGridData.m_blueprint.m_gridHeight; y++) {
			if (m_protoGridData.m_grid[coordinate(x, y).getIndex(m_protoGridData.m_blueprint)] == getTileTypeFromLegend('r')) {
				// Scan range four way for checking surrounding tiles to see the amount of other room floor tiles.
				std::vector<ETileType> floorSymbols = { getTileTypeFromLegend('r'), getTileTypeFromLegend('i'), getTileTypeFromLegend('f') };
				int neighborCount = 
					tileScanner.countSurroundingTiles(
						coordinate(x, y),
						m_protoGridData.m_blueprint,
						m_protoGridData.m_grid,
						NeighborCheckMode::FourWay,
						floorSymbols
						);
				// if 2 then corner floor tile, if 3 then wall floor tile, if 4 no change to do.
				if (neighborCount == 2) {
					m_protoGridData.m_grid[coordinate(x, y).getIndex(m_protoGridData.m_blueprint)] = getTileTypeFromLegend('i'); // Change to corner floor tile
				} else if (neighborCount == 3) {
					m_protoGridData.m_grid[coordinate(x, y).getIndex(m_protoGridData.m_blueprint)] = getTileTypeFromLegend('f'); // Change to wall floor tile
				}
			}




		}
	}
}

void BasicTileProcessor::processEntryPoints(){


	m_protoGridData.m_grid[m_protoGridData.entryPoints.first.getIndex(m_protoGridData.m_blueprint)] = getTileTypeFromLegend('='); // Set entry point tile
	m_protoGridData.m_grid[m_protoGridData.entryPoints.second.getIndex(m_protoGridData.m_blueprint)] = getTileTypeFromLegend('#'); // Set entry point tile

}


bool BasicTileProcessor::validate() {
    return true;
}