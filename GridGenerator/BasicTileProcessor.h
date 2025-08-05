#pragma once

#include "ITileProcessor.h"
#include "GridBlueprint.h"
#include "TileScanner.h"
#include <vector>
#include "coordinate.h"
#include "gridData.h"


class BasicTileProcessor : public ITileProcessor {

private:

    ProtoGridData m_protoGridData;
    TileScanner m_tileScanner;
    std::vector<std::pair<coordinate, coordinate>> m_roomList;

protected:
    // Intended to be called by the generate method.
    void processWalls() override;
    void processDoors() override;
    void processFloors() override;
	void processEntryPoints() override;

public:
	BasicTileProcessor();
    BasicTileProcessor(ProtoGridData protoGridData);

    ProtoGridData generate(ProtoGridData protoGridData) override;
    bool validate() override;


};

