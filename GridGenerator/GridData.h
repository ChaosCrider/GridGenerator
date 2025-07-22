#pragma once

#include <vector>
#include "eTileType.h"
#include "Coordinate.h"
#include "GridBlueprint.h"

class GridData {
public:
    GridData(const std::vector<ETileType> grid, const GridBlueprint& blueprint);
    int getWidth() const;
    int getHeight() const;
    ETileType getTile(int x, int y) const;

private:
    const std::vector<ETileType> m_grid;
    const GridBlueprint& m_blueprint;
};