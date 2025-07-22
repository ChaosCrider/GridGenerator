#pragma once

#include <vector>

class IWallMapper {
public:
    std::vector<std::vector<ETileType>> m_grid;

private:
    virtual ETileType process() = 0;
};