#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "GridConfig/GridBlueprint.h"
#include "3dSpace/eTileType.h"
#include "TileSpawner/ITileSpawner.h"
#include "TileFinder/ITileFinder.h"
#include "GridConfig/eGenerationSteps.h"

class GridGenerator {
    private:
        GridBlueprint m_blueprint;
        std::unordered_map<eTileType, std::unique_ptr<int>> m_assetMap;
        ITileSpawner* m_tileSpawner;
        ITileFinder* m_tileFinder;
        std::unordered_map<eGenerationSteps, ITileSpawner*> m_tileSpawnerStrategy;
        std::unordered_map<eGenerationSteps, ITileSpawner*> m_tileSpawnerStrategy;
        std::unordered_map<eGenerationSteps, ITileFinder*> m_tileFinderStrategy;
        std::vector<std::vector<eTileType>> m_grid;

        void setTileFinder(eGenerationSteps genStep);
        void setTileSpawner(eGenerationSteps genStep);
        void findTile(eTileType tileType);
        void spawnTile(eTileType tileType);

    public:
        GridGenerator(GridBlueprint blueprint);
        std::vector<std::vector<eTileType>> generate();
        void loadTileSet(std::unordered_map<eTileType, std::unique_ptr<int>> tileset);

};
