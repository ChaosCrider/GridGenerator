#pragma once

#include "../3dSpace/eTileType.h"

class ITileFinder{
private:
    eTileType m_tileMarquer = x;

public:
    virtual eTileType scanTile() = 0;
};


