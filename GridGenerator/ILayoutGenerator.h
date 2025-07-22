#pragma once

#include <vector>
#include <memory>
#include "eTileType.h"
#include "GridBlueprint.h"
#include "IRoomMapper.h"
#include "ICorridorMapper.h"

class ILayoutGenerator {

protected:
    // the Level represented as a 2D vector
    std::vector<ETileType> m_grid;

    // The different strategy used to map the general layout of the level.
    std::shared_ptr<IRoomMapper> roomMapper;
    std::shared_ptr<ICorridorMapper> corridorMapper;

    // Intended to be called by the generate method.
    virtual void generateRoomList() = 0;
    virtual void generateCorridor() = 0;

public:
    // entry point of the logic, use to insert the different elements to prepare what gameobject should go where.
    virtual std::vector<ETileType> generate(GridBlueprint blueprint, std::vector<ETileType> grid) = 0;

    //necessary to amke sure the resulting map is usable.
    virtual bool validate() = 0;

};