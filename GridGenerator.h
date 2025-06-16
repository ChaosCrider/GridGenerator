#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "GridConfig/GridBlueprint.h"
#include "3dSpace/eTileType.h"
#include "TileProcessing/ITileSpawner.h"
#include "TileProcessing/ITileFinder.h"
#include "GridConfig/eGenerationSteps.h"
#include "TileProcessing/ICorridorMapper.h"
#include "TileProcessing/GridIterator.h"

class GridGenerator {
    private:
        GridBlueprint m_blueprint;
        std::unordered_map<eTileType, std::unique_ptr<int>> m_assetMap;
        ITileFinder* m_tileFinder;
        ICorridorMapper* m_coddirdorMapper;
        ITileSpawner* m_tileSpawner;
        GridIterator* m_gridIterator;
        std::unordered_map<eGenerationSteps, ITileSpawner*> m_tileSpawnerStrategy;
        std::unordered_map<eGenerationSteps, ITileSpawner*> m_tileSpawnerStrategy;
        std::unordered_map<eGenerationSteps, ITileFinder*> m_tileFinderStrategy;
        std::vector<std::vector<eTileType>> m_grid;

        void setTileFinder(eGenerationSteps genStep);
        void setTileSpawner(eGenerationSteps genStep);
        void setCorridorMapper(eGenerationSteps genStep);

    public:
        GridGenerator(GridBlueprint blueprint);
        std::vector<std::vector<eTileType>> generate();
        void loadTileSet(std::unordered_map<eTileType, std::unique_ptr<int>> tileset);

};
