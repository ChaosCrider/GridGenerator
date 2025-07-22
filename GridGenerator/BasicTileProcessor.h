#pragma once

#include "ITileProcessor.h"



class BasicTileProcessor : public ITileProcessor {

protected:
    // Intended to be called by the generate method.
    ETileType processWalls() override;
    ETileType processDoors() override;
    ETileType processFloors() override;


public:
    BasicTileProcessor()
    {
    }

    std::vector<ETileType> generate(std::vector<ETileType> grid) override;
    bool validate() override;


};

