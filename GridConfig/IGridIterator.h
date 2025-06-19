#pragma once

#include <vector>
#include <memory>
#include "../3dSpace/eTileType.h"
#include "../TileProcessing/ITileProcessor.h"
#include "../LevelSculptor/IFeatureMapper.h"

 // is this still needed, possibly within the ITileProcessor & ILayoutGenerator

class IGridIterator{
    private :
        std::vector<std::vector<eTileType>> m_grid;

    public : 
        virtual std::vector<std::vector<eTileType>> iterate(std::shared_ptr<ITileProcessor> processor, std::vector<std::vector<eTileType>> m_grid) = 0;
        virtual std::vector<std::vector<eTileType>> iterate(std::shared_ptr<ILayoutGenerator> mapper, std::vector<std::vector<eTileType>> m_grid) = 0;
        virtual bool validate() = 0;
};