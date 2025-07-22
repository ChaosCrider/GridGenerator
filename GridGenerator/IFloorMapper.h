#pragma once

#include <vector>

class IFloorMapper {
public:
    std::vector<std::vector<ETileType>> m_grid;

private:
    virtual ETileType process() = 0;
};