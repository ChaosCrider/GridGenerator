#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

#include "GridManager.h"
#include "GridData.h"
#include "ITileProcessor.h"

GridManager::GridManager(GridBlueprint blueprint, std::shared_ptr<ITileProcessor> tileProcessor, std::shared_ptr<ILayoutGenerator> layoutGenerator)
    : m_blueprint(blueprint), m_layoutGenerator(layoutGenerator), m_tileProcessor(tileProcessor) {
}

const GridData& GridManager::generate() {

    //Generate the empty grid
    std::vector<ETileType> m_grid = std::vector<ETileType>(m_blueprint.m_gridHeight * m_blueprint.m_gridWidth, ETileType::empty);
    m_grid = m_layoutGenerator->generate(m_blueprint, m_grid);
    std::vector<ETileType> m_sculptedGrid;


    //m_grid = m_tileProcessor->generate(m_grid);
    m_gridData.emplace(m_grid, m_blueprint);

    return *m_gridData;
}

void spawnLevel(std::vector<std::vector<ETileType>> grid) {
    std::vector<std::vector<ETileType>> m_grid = grid;
}