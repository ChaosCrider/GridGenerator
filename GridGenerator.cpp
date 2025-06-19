#include "GridGenerator.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

GridGenerator::GridGenerator(GridBlueprint blueprint)
    : m_blueprint(blueprint) {}

std::vector<std::vector<eTileType>> GridGenerator::generate(){

    //Generate the empty grid
    std::vector<std::vector<eTileType>> m_grid = std::vector<std::vector<eTileType>>(m_blueprint.m_gridHeight, std::vector<eTileType>(m_blueprint.m_gridWidth, eTileType::x));

    /* vestigial
    
        //Generate rooms
    std::shared_ptr<ILayoutGenerator> generator = std::dynamic_pointer_cast<ILayoutGenerator>(m_roomMapper);
    if (generator){
        m_gridIterator->iterate(generator, m_grid);
        if(!generator->validate()){
            std::cout << "error on Room Generation";
        }
    }

    //Links room with corridors
    generator = std::dynamic_pointer_cast<ILayoutGenerator>(m_corridorMapper);
    if (generator){
        m_gridIterator->iterate(generator, m_grid);
        if(!generator->validate()){
            std::cout << "error on Corridor Generation";
        }
    }

    //Change unprocessed tile into walls, floors and doors.
    std::shared_ptr<ITileProcessor> processor = std::dynamic_pointer_cast<ITileProcessor>(m_tileSpawner);
    if (processor){
        m_gridIterator->iterate(processor, m_grid);
        if(!processor->validate()){
            std::cout << "error on Tile Type assignment";
        }
    }



    */

    m_grid = layoutGenerator->generate(m_blueprint, m_grid);
    
    m_grid = tileProcessor->generate(m_grid);


    return m_grid;
}

void spawnLevel(std::vector<std::vector<eTileType>> grid){
        std::vector<std::vector<eTileType>> m_grid = grid;
}