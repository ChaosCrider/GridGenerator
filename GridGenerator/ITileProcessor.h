#pragma once

#include <vector>
#include "eTileType.h"
#include "IWallMapper.h"
#include "IDoorMapper.h"
#include "IFloorMapper.h"
#include "GridBlueprint.h"
#include "Coordinate.h"
#include "gridData.h"

class ITileProcessor {
protected:

    // Intended to be called by the generate method.
    virtual void processWalls() = 0;
    virtual void processDoors() = 0;
    virtual void processFloors() = 0;
    virtual void processEntryPoints() = 0;

    // Protected default constructor to allow inheritance
    ITileProcessor() = default;

    // Protected virtual destructor to ensure proper cleanup
    virtual ~ITileProcessor() = default;

public:

    // Entry point of the logic, use to insert the different elements to prepare what game object should go where.
    virtual ProtoGridData generate(ProtoGridData protoGridData) = 0;

    // Necessary to make sure the resulting map is usable.
    virtual bool validate() = 0;
};