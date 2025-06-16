#include "GridGenerator.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

GridGenerator::GridGenerator(GridBlueprint blueprint)
    : m_gridIterator(),
    m_blueprint(blueprint) {}

void GridGenerator::loadTileSet(std::unordered_map<eTileType, std::unique_ptr<int>> tileset){
    m_assetMap = std::move(tileset);
}

void GridGenerator::setTileSpawner(eGenerationSteps genStep){
    auto hit = m_tileSpawnerStrategy.find(genStep);
    if (hit != m_tileSpawnerStrategy.end()){
        m_tileSpawner = m_tileSpawnerStrategy[genStep];
    }
}

void GridGenerator::setTileFinder(eGenerationSteps genStep){
    auto hit = m_tileFinderStrategy.find(genStep);
    if (hit != m_tileFinderStrategy.end()) {
        m_tileFinder = m_tileFinderStrategy[genStep];   
    }
}

std::vector<std::vector<eTileType>> GridGenerator::generate(){
    m_grid = std::vector<std::vector<eTileType>>(m_blueprint.m_gridHeight, std::vector<eTileType>(m_blueprint.m_gridWidth, eTileType::x));

    ITileProcessor* processor = dynamic_cast<ITileProcessor*>(m_tileFinder);
    if (processor){
        m_gridIterator->iterate(processor, m_grid);
        if(!processor->validate()){
            std::cout << "error on Room Generation";
        }
    }

    processor = dynamic_cast<ITileProcessor*>(m_coddirdorMapper);
    if (processor){
        m_gridIterator->iterate(processor, m_grid);
        if(!processor->validate()){
            std::cout << "error on Corridor Generation";
        }
    }

        processor = dynamic_cast<ITileProcessor*>(m_tileSpawner);
    if (processor){
        m_gridIterator->iterate(processor, m_grid);
        if(!processor->validate()){
            std::cout << "error on Tile Type assignment";
        }
    }

    return m_grid;
}