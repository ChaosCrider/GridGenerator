#pragma once

#include <vector>
#include "eTileType.h"

class IRoomMapper {
public:
    std::vector<std::vector<ETileType>> m_grid;

private:
    virtual ETileType process() = 0;
};