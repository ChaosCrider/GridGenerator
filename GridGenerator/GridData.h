#pragma once

#include <vector>
#include "eTileType.h"
#include "Coordinate.h"
#include "GridBlueprint.h"

class ProtoGridData {
public:
    ProtoGridData(std::vector<ETileType> grid, GridBlueprint blueprint);
    std::vector<ETileType> m_grid;
    GridBlueprint m_blueprint;
    std::vector<std::pair<coordinate, coordinate>> m_roomList;
    std::pair<coordinate, coordinate> entryPoints;
};

class GridData {
public:
    GridData(const ProtoGridData other);
    GridData(const std::vector<ETileType> grid, const GridBlueprint blueprint, const std::vector<std::pair<coordinate, coordinate>> roomList, const std::pair<coordinate, coordinate> entryPoints);
	~GridData() = default;

    int debugLength() const;
    int getWidth() const;
    int getHeight() const;
    ETileType getTile(int x, int y) const;

private:
    const std::vector<ETileType> m_grid;
    const GridBlueprint m_blueprint;
    const std::vector<std::pair<coordinate, coordinate>> m_roomList;
	const std::pair<coordinate, coordinate> entryPoints;
};
