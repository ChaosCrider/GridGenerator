#pragma once

#include "Coordinate.h"
#include <optional>
#include <vector>
#include "ETileType.h"

// Enum to choose whether we check 4-way (up/down/left/right) or 8-way (including diagonals)
enum class NeighborCheckMode {
	TwoWayVertical,
	TwoWayHorizontal,
	FourWay,
	EightWay
};

class TileScanner
{
public:
	TileScanner();
	int countSurroundingTiles(coordinate center, const GridBlueprint& blueprint, const std::vector<ETileType>& grid, NeighborCheckMode mode, std::optional<std::vector<ETileType>> filter = std::nullopt);
	std::vector<coordinate> scanForWall(coordinate center, const std::vector<ETileType>& grid, const GridBlueprint& blueprint);
	ETileType scanWallType(coordinate tile, std::vector<ETileType>& grid, GridBlueprint& blueprint);
};

