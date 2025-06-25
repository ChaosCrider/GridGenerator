#pragma once

#include <vector>
#include "../3dSpace/eTileType.h"
#include "IWallMapper.h"
#include "IDoorMapper.h"
#include "IFloorMapper.h"

class ITileProcessor{
    private :

        // the Level represented as a 2D vector
        std::vector<std::vector<eTileType>> m_grid;

        // The different strategy used to assign what type of object goes where.
        std::shared_ptr<IWallMapper> wallMapper;
        std::shared_ptr<IDoorMapper> doorMapper;
        std::shared_ptr<IFloorMapper> FloorMapper;

        // Intended to be called by the generate method.
        virtual eTileType processWalls() = 0;
        virtual eTileType processDoors() = 0;
        virtual eTileType processFloors() = 0;

    public :

        // entry point of the logic, use to insert the different elements to prepare what game object should go where.
        virtual std::vector<std::vector<eTileType>> generate(std::vector<std::vector<eTileType>> grid);

        //necessary to amke sure the resulting map is usable.
        virtual bool validate() = 0;
};