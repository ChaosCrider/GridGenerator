#pragma once

#include "ITileProcessor.h"
#include "GridBlueprint.h"
#include "TileScanner.h"


class BasicTileProcessor : public ITileProcessor {

private:
    std::vector<ETileType> m_grid;
	GridBlueprint m_blueprint;
    TileScanner m_tileScanner;

protected:
    // Intended to be called by the generate method.
    void processWalls() override;
    void processDoors() override;
    void processFloors() override;


public:
    BasicTileProcessor();

    std::vector<ETileType> generate(std::vector<ETileType>& grid, GridBlueprint& blueprint) override;
    bool validate() override;


};

