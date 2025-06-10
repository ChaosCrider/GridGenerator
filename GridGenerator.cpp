#include "GridGenerator.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

GridGenerator::GridGenerator(GridBlueprint blueprint)
    : m_blueprint(blueprint) {}

std::vector<std::vector<eTileType>> GridGenerator::generate(){
    m_grid = std::vector<std::vector<eTileType>>(m_blueprint.m_gridHeight, std::vector<eTileType>(m_blueprint.m_gridWidth, eTileType::x));
    return m_grid;
}

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

void GridGenerator::findTile(eTileType tileType){

}

void GridGenerator::spawnTile(eTileType tileType){

}