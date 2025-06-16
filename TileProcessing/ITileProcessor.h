#pragma once

#include <vector>
#include "../3dSpace/eTileType.h"

class ITileProcessor{
    private :
        std::vector<std::vector<eTileType>> m_grid;

    public :
        virtual eTileType process() = 0;
        virtual bool validate() = 0;
};