#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <optional>
#include "GridBlueprint.h"
#include "eTileType.h"
#include "GridData.h"
#include "ICorridorMapper.h"
#include "IRoomMapper.h"
#include "ILayoutGenerator.h"
#include "ITileProcessor.h"

class GridManager {
private:
    GridBlueprint m_blueprint;

    std::unordered_map<ETileType, std::unique_ptr<int>> m_assetMap;
    std::optional<GridData>  m_gridData;

    std::shared_ptr<ITileProcessor> m_tileProcessor;
    std::shared_ptr<ILayoutGenerator> m_layoutGenerator;

public:
    GridManager(GridBlueprint blueprint, std::shared_ptr<ITileProcessor> tileProcessor, std::shared_ptr<ILayoutGenerator> layoutGenerator);
    const GridData& generate();

};
