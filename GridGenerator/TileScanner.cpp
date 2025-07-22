#include "TileScanner.h"
#include "coordinate.h"
#include "eTileType.h"
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

int TileScanner::countSurroundingTiles(coordinate center, int width, int height, const std::vector<ETileType>& grid, NeighborCheckMode mode, std::optional<ETileType> filter)
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

    // Loop over each neighboring direction
    for (auto [dx, dy] : directions) {
        int nx = center.x + dx; // Neighbor X
        int ny = center.y + dy; // Neighbor Y

        // Convert 2D coords to 1D index in the flat grid vector
        int index = ny * width + nx;
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
