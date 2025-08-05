#include "GridData.h"
#include "eTileType.h"
#include <iostream>




GridData::GridData(const std::vector<ETileType> grid, const GridBlueprint blueprint, const std::vector<std::pair<coordinate, coordinate>> roomList, const std::pair<coordinate, coordinate> entryPoints)
    : m_grid(grid),
    m_blueprint(blueprint),
    m_roomList(roomList),
    entryPoints(entryPoints)
{
}

GridData::GridData(const ProtoGridData other)
    : m_grid(other.m_grid),
      m_blueprint(other.m_blueprint),
      m_roomList(other.m_roomList), 
	entryPoints(other.entryPoints)
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

ProtoGridData::ProtoGridData(std::vector<ETileType> grid, GridBlueprint blueprint)
    :m_grid(grid), m_blueprint(blueprint), m_roomList({}), entryPoints({{0, 0},{0, 0}})
{
}

int GridData::debugLength() const{
    return m_grid.size();
}