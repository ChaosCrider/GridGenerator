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
    int countSurroundingTiles( coordinate center, int width, int height, const std::vector<ETileType>& grid, NeighborCheckMode mode, std::optional<ETileType> filter = std::nullopt);
};

