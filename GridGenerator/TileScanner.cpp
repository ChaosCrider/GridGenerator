#include "TileScanner.h"
#include "coordinate.h"
#include "eTileType.h"
#include "GridBlueprint.h"
#include <vector>
#include <optional>
#include <iostream>


TileScanner::TileScanner(){}

/*
 * Counts the number of neighboring tiles around a given center coordinate.
 * You can choose between 4-way or 8-way neighbors.
 * If a filter is provided, only tiles of that type are counted.
 * If no filter is provided, all tiles that are not ETileType::None are counted.
 */

int TileScanner::countSurroundingTiles(coordinate center, const GridBlueprint& blueprint, const std::vector<ETileType>& grid, NeighborCheckMode mode, std::optional<ETileType> filter)
{
    int count = 0; // Total count of matching neighbors

    std::vector<std::pair<int, int>> directions;

    switch (mode) {
        case NeighborCheckMode::TwoWayVertical:
            directions = {
                {0, 1},   // Down
                {0, -1}   // Up
            };
			break;
        case NeighborCheckMode::TwoWayHorizontal:
            directions = {
                {1, 0},   // Right
                {-1, 0}   // Left
			};
            break;
        case NeighborCheckMode::FourWay :
            directions = {
                {1, 0},   // Right
                {-1, 0},  // Left
                {0, 1},   // Down
                {0, -1}   // Up
            };
            break;
        case NeighborCheckMode::EightWay:
            directions = {
                {1, 0},   // Right
                {-1, 0},  // Left
                {0, 1},   // Down
                {0, -1},  // Up
                {1, 1},   // Down-Right
                {-1, -1}, // Up-Left
                {1, -1},  // Up-Right
                {-1, 1}   // Down-Left
            };
            break;
		default:
            directions = {
                {1, 0},   // Right
                {-1, 0},  // Left
                {0, 1},   // Down
                {0, -1},  // Up
                {1, 1},   // Down-Right
                {-1, -1}, // Up-Left
                {1, -1},  // Up-Right
                {-1, 1}   // Down-Left
            };
            break;

    }


    int x = center.x;
    int y = center.y;
    // Loop over each neighboring direction
    for (auto [dx, dy] : directions) {
        int nx = x + dx; // Neighbor X
        int ny = y + dy; // Neighbor Y

        // Convert 2D coords to 1D index in the flat grid vector
        int index = coordinate(ny, nx).getIndex(blueprint);
        ETileType tile = grid[index];

        // If a filter is provided, only count tiles that match it
        if (filter.has_value()) {
            if (tile == filter.value()) {
                count++;
            }
        }
        else {
            // Otherwise, count all non-empty tiles (not ETileType::None)
            if (tile != ETileType::empty) {
                count++;
            }
        }
    }
    return count; // Final count of matching tiles
}


std::vector<coordinate> TileScanner::scanForWall(coordinate center, const std::vector<ETileType>& grid, const GridBlueprint& blueprint)
{

    /*
    Scans the surrounding tiles of a given center coordinate for emtpy cells that woule be valid walls
    */

    std::vector<coordinate> wallsFound;

    std::vector<std::pair<int, int>> directions = {
    {1, 0},   // Right
    {-1, 0},  // Left
    {0, 1},   // Down
    {0, -1}   // Up
    };

    for (auto [dx, dy] : directions) {
        int nx = center.x + dx; // Neighbor X
        int ny = center.y + dy; // Neighbor Y
        // Convert 2D coords to 1D index in the flat grid vector
        int index = ny * blueprint.m_gridWidth + nx;
        ETileType tile = grid[index];
        if (tile == getTileTypeFromLegend('x')) {
            wallsFound.emplace_back(coordinate(nx, ny)); // Return the first wall found
        }
	}

	return wallsFound; // Return the vector of wall coordinates
}

ETileType TileScanner::scanWallType(coordinate tile, std::vector<ETileType>& grid, GridBlueprint& blueprint)
{
	bool vhit = false; // Vertical hit
	bool hhit = false; // Horizontal hit
	int count = 0; // Count of hits
	int x = tile.x; // X coordinate of the tile
	int y = tile.y; // Y coordinate of the tile

	// scan both horizontal and vertical neighbors of the tile.
    // track both number of hit as well as if both axis are a hit.
    // scan left

    #pragma region Scan sides

        ETileType interogatedTile = grid[coordinate(x - 1, y).getIndex(blueprint)];
        if (interogatedTile == getTileTypeFromLegend('c') || interogatedTile == getTileTypeFromLegend('f')) {
		    vhit = true; // Vertical hit found
            count++;
        }

	    // scan right
        interogatedTile = grid[coordinate(x + 1, y).getIndex(blueprint)];
        if (interogatedTile == getTileTypeFromLegend('c') || interogatedTile == getTileTypeFromLegend('f')) {
            vhit = true; // Vertical hit found
            count++;
        }

	    // scan up
        interogatedTile = grid[coordinate(x, y - 1).getIndex(blueprint)];
        if (interogatedTile == getTileTypeFromLegend('c') || interogatedTile == getTileTypeFromLegend('f')) {
            vhit = true; // Vertical hit found
            count++;
        }

	    // scan down
        interogatedTile = grid[coordinate(x, y + 1).getIndex(blueprint)];
        if (interogatedTile == getTileTypeFromLegend('c') || interogatedTile == getTileTypeFromLegend('f')) {
            vhit = true; // Vertical hit found
            count++;
        }
    #pragma endregion

	// if both axis are a hit, return ETileType::InnerCornerWallFloor.
    if (vhit && hhit) { return getTileTypeFromLegend('l'); }

    // then scan the corner tiles and compile the total number of hits.
    std::vector<coordinate> fourCorners = {
        coordinate(x - 1, y - 1), // Top-Left
        coordinate(x + 1, y - 1), // Top-Right
        coordinate(x - 1, y + 1), // Bottom-Left
        coordinate(x + 1, y + 1)  // Bottom-Right
	};
    for (const auto& corner : fourCorners) {
        interogatedTile = grid[coordinate(corner.x, corner.y).getIndex(blueprint)];
        if (interogatedTile == getTileTypeFromLegend('c') || interogatedTile == getTileTypeFromLegend('f')) {
            count++;
        }
    }
    // if the number of hit is 1, then return ETileType::WallFloor.
    if (count == 1) {
		return getTileTypeFromLegend('.'); // corner wall tile
    }
    // else return ETileType::CornerWalledFloor.
    else if (count > 1) {
		return getTileTypeFromLegend('w'); // wall tile
    }
    else {
		return getTileTypeFromLegend('x'); // empty tile
    }
}

