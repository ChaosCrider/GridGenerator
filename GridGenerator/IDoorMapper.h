#pragma once

#include <vector>

class IDoorMapper {
public:
    std::vector<std::vector<ETileType>> m_grid;

private:
    virtual ETileType process() = 0;
};