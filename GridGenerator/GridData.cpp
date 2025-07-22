#include "GridData.h"
#include "eTileType.h"
#include <iostream>


GridData::GridData(const std::vector<ETileType> grid, const GridBlueprint& blueprint)
    :
    m_grid(grid),
    m_blueprint(blueprint)
{
}

int GridData::getWidth() const {
    return m_blueprint.m_gridWidth;
}

int GridData::getHeight() const {
    return m_blueprint.m_gridHeight;
}

ETileType GridData::getTile(int x, int y) const {
    return m_grid[(y * m_blueprint.m_gridWidth) + x];
}