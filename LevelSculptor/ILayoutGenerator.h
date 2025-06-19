#pragma once

#include <vector>
#include <memory>
#include "../3dSpace/eTileType.h"
#include "IRoomMapper.h"
#include "ICorridorMapper.h"

class ILayoutGenerator{

        // the Level represented as a 2D vector
        std::vector<std::vector<eTileType>> m_grid;

        // The different strategy used to map the general layout of the level.
        std::shared_ptr<IRoomMapper> roomMapper;
        std::shared_ptr<ICorridorMapper> corridorMapper;

        // Intended to be called by the generate method.
        virtual void placeRooms();
        virtual void placeCorridors();

    public : 

        // vestigial
        virtual std::vector<std::vector<eTileType>> iterate(GridBlueprint blueprint, std::vector<std::vector<eTileType>> grid) = 0;

        // entry point of the logic, use to insert the different elements to prepare what gameobject should go where.
        virtual std::vector<std::vector<eTileType>> generate(GridBlueprint blueprint, std::vector<std::vector<eTileType>> grid) = 0;

        //necessary to amke sure the resulting map is usable.
        virtual bool validate() = 0;

};