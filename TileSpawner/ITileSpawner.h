#pragma once
#include <unordered_map>
#include <memory>
#include "../3dSpace/eTileType.h"

class ITileSpawner{
private:
    std::unordered_map<eTileType, std::unique_ptr<int>> m_assetMap;

public:
    virtual void spawn() = 0;
    virtual ~ITileSpawner();
};