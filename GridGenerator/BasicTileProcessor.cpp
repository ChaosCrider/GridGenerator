#include <vector>
#include "BasicTileProcessor.h"
#include "ITileProcessor.h"
#include "eTileType.h"

ETileType BasicTileProcessor::processWalls() {

    if (true)
    {
        return ETileType::StraigthWall;
    }
    else
    {
        return ETileType::empty;
    }
}

ETileType BasicTileProcessor::processDoors() {
    if (true)
    {
        return ETileType::Door;
    }
    else
    {
        return ETileType::empty;
    }
}

ETileType BasicTileProcessor::processFloors() {
    if (true)
    {
        return ETileType::RoomFloor;
    }
    else
    {
        return ETileType::empty;
    }
}

std::vector<ETileType> BasicTileProcessor::generate(std::vector<ETileType> grid) {
    return grid;
}

bool BasicTileProcessor::validate() {
    return true;
}