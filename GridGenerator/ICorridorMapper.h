#pragma once

#include <vector>
#include "eTileType.h"

class ICorridorMapper {
public:
    std::vector<std::vector<ETileType>> m_grid;

private:
    virtual ETileType process() = 0;
};