#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "GridConfig/GridBlueprint.h"
#include "3dSpace/eTileType.h"
#include "GridConfig/eGenerationSteps.h"
#include "LevelSculptor/ICorridorMapper.h"
#include "LevelSculptor/IRoomMapper.h"
#include "GridConfig/IGridIterator.h"
#include "LevelSculptor/ILayoutGenerator.h"

class GridGenerator {
    private:
        GridBlueprint m_blueprint;
        std::unordered_map<eTileType, std::unique_ptr<int>> m_assetMap;

        std::shared_ptr<ITileProcessor> tileProcessor;
        std::shared_ptr<ILayoutGenerator> layoutGenerator;

    public:
        GridGenerator(GridBlueprint blueprint);
        std::vector<std::vector<eTileType>> generate();

};
