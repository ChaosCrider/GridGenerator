#pragma once

#include <vector>
#include "eTileType.h"
#include "IWallMapper.h"
#include "IDoorMapper.h"
#include "IFloorMapper.h"

class ITileProcessor {
protected:

    // the Level represented as a 2D vector
    std::vector<ETileType> m_grid;

    // Intended to be called by the generate method.
    virtual ETileType processWalls() = 0;
    virtual ETileType processDoors() = 0;
    virtual ETileType processFloors() = 0;

public:

    // entry point of the logic, use to insert the different elements to prepare what game object should go where.
    virtual std::vector<ETileType> generate(std::vector<ETileType> grid) = 0;

    //necessary to amke sure the resulting map is usable.
    virtual bool validate() = 0;
};