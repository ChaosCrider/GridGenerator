#pragma once
#include "ILayoutGenerator.h"
#include "eTileType.h"
#include "GridBlueprint.h"
#include "RandomCoordGenerator.h"
#include "gridData.h"

class BasicLayoutGenerator : public ILayoutGenerator {

protected:
    void generateRoomList() override;
    void generateCorridor() override;

private:
    std::vector<std::pair<coordinate, coordinate>> m_roomList;
    std::vector<corridor> corridorTree;
    GridBlueprint m_blueprint;
    RandomCoordGenerator m_rCoordGen;
    const int MAX_LOOP = 30;
    const int CORRIDOR_SPACE = 3;

    void sortRoomLinks(std::vector<corridor>& corridorCandidates);
    void writeRoom();
    void writeCorridor();
	void bufferCorridor(coordinate& midPoint, coordinate& upperAncor, coordinate& lowerAncor);
    void writeHorizontalCorridor(coordinate room, coordinate midPoint);
    void writeVerticalCorridor(coordinate room, coordinate midPoint);
    bool isRoomValid(const coordinate& point1, const coordinate& point2);
    std::pair<coordinate, coordinate> makeRoomCoordinates();
    bool tryAddRoom();
	std::pair<coordinate, coordinate> createEntryPoints();
	void writeEntryPoints(ProtoGridData tempGridData);

    std::vector<corridor> createCorridorCandidate(std::vector<std::pair<coordinate, coordinate>> roomList);

public:

    BasicLayoutGenerator();
    ~BasicLayoutGenerator();

    ProtoGridData generate(ProtoGridData protoGridData) override;
    bool validate() override;
};

