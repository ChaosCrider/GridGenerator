#pragma once

#include <vector>
#include "../3dSpace/eTileType.h"
#include "ITileProcessor.h"


class GridIterator{
    private :
        std::vector<std::vector<eTileType>> m_grid;

    public : 
        std::vector<std::vector<eTileType>> iterate(ITileProcessor* processor, std::vector<std::vector<eTileType>> m_grid);
};