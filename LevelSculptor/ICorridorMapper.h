#pragma once

#include <vector>
#include "../3dSpace/eTileType.h"

class ICorridorMapper {
    public:
        std::vector<std::vector<eTileType>> m_grid;

    private:
        virtual eTileType process() = 0;
};