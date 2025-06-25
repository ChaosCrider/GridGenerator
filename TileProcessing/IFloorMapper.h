#pragma once

class IFloorMapper{
    public:
        std::vector<std::vector<eTileType>> m_grid;

    private:
        virtual eTileType process() = 0;
};