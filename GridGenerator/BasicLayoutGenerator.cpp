
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "BasicLayoutGenerator.h"
#include "eTileType.h"
#include "Coordinate.h"
#include "RandomCoordGenerator.h"
#include "UnionFinder.h"
#include "TileScanner.h"

#pragma region Constructor/Destructor

    BasicLayoutGenerator::~BasicLayoutGenerator() = default;

    BasicLayoutGenerator::BasicLayoutGenerator() : m_roomList(), m_blueprint(), m_rCoordGen(), corridorTree() {}

#pragma endregion

#pragma region Public Methods
//public methods

    std::vector<ETileType> BasicLayoutGenerator::generate(GridBlueprint blueprint, std::vector<ETileType> grid) {

        m_grid = grid;
        m_blueprint = blueprint;
        generateRoomList();
        writeRoom();
        generateCorridor();
        writeCorridor();

        return m_grid;
    }

    bool BasicLayoutGenerator::validate() {
        return true;
    }

#pragma endregion

#pragma region Protected Methods
//protected methods

    void BasicLayoutGenerator::generateRoomList() {
        m_roomList.clear(); // Start fresh
        while (m_roomList.size() < m_blueprint.m_roomCount) {
            if (!tryAddRoom()) {
                break; // Stop if we can't place more rooms
            }
        }
    }

    void BasicLayoutGenerator::generateCorridor() {

        // Clear the previous corridor list
        corridorTree.clear();

        //create a list of potential corridors
        std::vector<corridor> corridorCandidates = createCorridorCandidate(m_roomList);

        //sort the list by length
        sortRoomLinks(corridorCandidates);

        // create unionFinder Object
        UnionFinder uf(m_roomList.size());

        // iterate through the sorted corridors
        // Kruskal’s Algorithm - use union-find to check if the rooms are connected.
        for (const auto& corridor : corridorCandidates) {
            auto u = corridor.start;
            auto v = corridor.end;
            if (!uf.connected(u, v)) {
                uf.unionSets(u, v); // Union the sets
                corridorTree.push_back(corridor); // Add to the final corridor list
            }
            if (corridorTree.size() == m_roomList.size() - 1) {
                break; // Stop if we have enough corridors for the MST
            }
        }
    }

#pragma endregion

#pragma region Private Methods
//private methods

    #pragma region Room Generation

        bool BasicLayoutGenerator::tryAddRoom() {
            for (int i = 0; i < MAX_LOOP; i++) { // Try up to MAX_LOOP times
                auto [point1, point2] = makeRoomCoordinates();
                if (isRoomValid(point1, point2)) {
                    m_roomList.emplace_back(point1, point2); // Add room
                    return true; // Success
                }
            }
            return false; // Failed after MAX_LOOP tries
        }

        std::pair<coordinate, coordinate> BasicLayoutGenerator::makeRoomCoordinates() {

            // Make point1 (top-left corner)
            int xMin = m_blueprint.m_gridEdgeBuffer;
            int xMax = m_blueprint.m_gridWidth - 1 - (m_blueprint.m_gridEdgeBuffer + m_blueprint.m_roomMaxSize);
            int yMin = m_blueprint.m_gridEdgeBuffer;
            int yMax = m_blueprint.m_gridHeight - 1 - (m_blueprint.m_gridEdgeBuffer + m_blueprint.m_roomMaxSize);
            coordinate point1 = m_rCoordGen.getRandomCoord(xMin, xMax, yMin, yMax);

            // Make point2 (bottom-right corner)
            xMin = point1.x + m_blueprint.m_roomMinSize;
            xMax = std::min(point1.x + m_blueprint.m_roomMaxSize, m_blueprint.m_gridWidth - m_blueprint.m_gridEdgeBuffer - 1);
            yMin = point1.y + m_blueprint.m_roomMinSize;
            yMax = std::min(point1.y + m_blueprint.m_roomMaxSize, m_blueprint.m_gridHeight - m_blueprint.m_gridEdgeBuffer - 1);
            coordinate point2 = m_rCoordGen.getRandomCoord(xMin, xMax, yMin, yMax);

            return { point1, point2 };
        }

        bool BasicLayoutGenerator::isRoomValid(const coordinate& point1, const coordinate& point2) {
            for (const auto& room : m_roomList) {
                if (
                    point2.x >= room.first.x - CORRIDOR_SPACE &&
                    point1.x <= room.second.x + CORRIDOR_SPACE &&
                    point2.y >= room.first.y - CORRIDOR_SPACE &&
                    point1.y <= room.second.y + CORRIDOR_SPACE
                    )
                {
                    return false; // Overlap found
                }
            }
            return true; // No overlap
        }

        void BasicLayoutGenerator::writeRoom() {
            // cycle trhough each room in m_roomList
            for (int i = 0; i < m_roomList.size(); i++)
            {
                // cycle through each row of current room
                    // from room.first.x to room.second.x
                for (int x = m_roomList[i].first.x; x <= m_roomList[i].second.x; x++)
                {
                    // cycle through each column of current room
                    // from room.first.y to room.second.y
                    for (int y = m_roomList[i].first.y; y <= m_roomList[i].second.y; y++)
                    {
                        // write floor tile
                        m_grid[x + (y * m_blueprint.m_gridWidth)] = getTileTypeFromLegend('r');
                    }
                }
            }
        }

        void BasicLayoutGenerator::sortRoomLinks(std::vector<corridor>& corridorCandidates) {
            // This function will sort the corridors based on their length
            std::sort(corridorCandidates.begin(), corridorCandidates.end(),
                [](const corridor& a, const corridor& b) {
                    return a.length < b.length;
                });
        }

    #pragma endregion

    #pragma region Corridor Generation

        #pragma region Corridor Calculation

            std::vector<corridor> BasicLayoutGenerator::createCorridorCandidate(std::vector<std::pair<coordinate, coordinate>> roomList)
            {
                std::vector<corridor> corridors;

                for (int i = 0; i < roomList.size(); ++i) {
                    for (int j = i + 1; j < roomList.size(); ++j) {
                        // Calculate Euclidean distance between room i and room j
                        double dx = static_cast<double>(roomList[i].first.x - roomList[j].first.x);
                        double dy = static_cast<double>(roomList[i].first.y - roomList[j].first.y);
                        int length = static_cast<int>(std::sqrt((dx * dx) + (dy * dy)));
                        corridors.push_back(corridor{ i, j, length});
                    }
                }

                return corridors;
            }

            void BasicLayoutGenerator::bufferCorridor(coordinate& midPoint, coordinate& upperAnchor, coordinate& lowerAnchor)
            {
                TileScanner scanner = TileScanner();

    
                // process vertical axis.
                // check for minimal length of 3 tiles on the axis
                if (midPoint.y - upperAnchor.y >= 2) {
                    // from min +1 to max -1, check for surounding obstacles using TileScanner
                    for (int y = upperAnchor.y + 1; y < midPoint.y-1; y++) {
                        // if not 0 then adjust midPoint.x and upperAncor.x by +1
                        if (scanner.countSurroundingTiles(coordinate(midPoint.x, upperAnchor.y), m_blueprint, m_grid, NeighborCheckMode::EightWay))
                            midPoint.x++;
    			            upperAnchor.x++;
                            break;
                        }
		            }

	            //process horizontal axis.
	            // check for minimal length of 3 tiles on the axis
                int x;
                int targetX;
                if (abs(midPoint.x - lowerAnchor.x) >= 2) {
                    // from min +1 to max -1, check for surounding obstacles using TileScanner
                    if (midPoint.x > lowerAnchor.x) {
                        targetX = midPoint.x - 1;
                        x = lowerAnchor.x + 1;
                    }
                    else {
                        targetX = midPoint.x + 1;
                        x = lowerAnchor.x - 1;
                    }
                    for (x; x < targetX; x++) {
                        // if not 0 then adjust midPoint.y and upperAncor.y by +1
                        coordinate tile = coordinate(upperAnchor.x, midPoint.y);
                        if (scanner.countSurroundingTiles(tile, m_blueprint, m_grid, NeighborCheckMode::EightWay)) {
                            midPoint.y++;
                            lowerAnchor.y++;
                            break;
                        }
                    }
                }


            }

        #pragma endregion

        #pragma region Corridor Writing

            void BasicLayoutGenerator::writeCorridor()
            {
                for (const auto& corridor : corridorTree) {

                    // Calculate the center point of room A by averaging its top-left and bottom-right coordinates
                    coordinate roomA(
                        (m_roomList[corridor.start].first.x + m_roomList[corridor.start].second.x) / 2,
                        (m_roomList[corridor.start].first.y + m_roomList[corridor.start].second.y) / 2
                    );

                    // Calculate the center point of room B
                    coordinate roomB(
                        (m_roomList[corridor.end].first.x + m_roomList[corridor.end].second.x) / 2,
                        (m_roomList[corridor.end].first.y + m_roomList[corridor.end].second.y) / 2
                    );

                    // Initialize the midpoint of the corridor connection
                    coordinate midPoint(0, 0);

                        // Determine corridor vertical direction: roomA is above roomB
                        if (roomA.y < roomB.y) {

                            // Midpoint is aligned horizontally with roomA, and vertically with roomB
                            midPoint = coordinate(roomA.x, roomB.y);

                            // Adjust roomA.y to the bottom edge of roomA (to avoid drawing corridor inside the room)
                            roomA.y = m_roomList[corridor.start].second.y;

                            // Depending on the horizontal relationship, adjust roomB.x to the edge of roomB
                            if (roomA.x < roomB.x) {
                                // roomB is to the right of roomA; use left edge of roomB
                                roomB.x = m_roomList[corridor.end].first.x;
                            }
                            else {
                                // roomB is to the left of roomA; use right edge of roomB
                                roomB.x = m_roomList[corridor.end].second.x;
                            }

                            // Handle potential overlap or padding around the L-shaped corridor
                            bufferCorridor(midPoint, roomA, roomB);

                            // Draw horizontal segment from roomB to the midpoint
                            writeHorizontalCorridor(roomB, midPoint);

                            // Draw vertical segment from roomA to the midpoint
                            writeVerticalCorridor(roomA, midPoint);
                        }

                        else {

                            // Midpoint is aligned horizontally with roomA, and vertically with roomB
                            midPoint = coordinate(roomA.x, roomB.y);

                            // Adjust roomA.y to the upper* edge of roomA (to avoid drawing corridor inside the room)
                            roomA.y = m_roomList[corridor.start].first.y;

                            // Depending on the horizontal relationship, adjust roomB.x to the edge of roomB
                            if (roomA.x < roomB.x) {
                                // roomB is to the right of roomA; use left edge of roomB
                                roomB.x = m_roomList[corridor.end].first.x;
                            }
                            else {
                                // roomB is to the left of roomA; use right edge of roomB
                                roomB.x = m_roomList[corridor.end].second.x;
                            }

                            // Handle potential overlap or padding around the L-shaped corridor
                            bufferCorridor(midPoint, roomA, roomB);

                            // Draw horizontal segment from roomB to the midpoint
                            writeHorizontalCorridor(roomB, midPoint);

                            // Draw vertical segment from roomA to the midpoint
                            writeVerticalCorridor(roomA, midPoint);
                        }
                }
            }

            void BasicLayoutGenerator::writeHorizontalCorridor(coordinate room, coordinate midPoint) {
                // Ensure room is always to the left of midPoint
                if (room.x > midPoint.x) {
                    std::swap(room, midPoint);
                }
                // Write horizontal corridor
                for (int x = room.x+1; x <= midPoint.x; x++) {;
                    ETileType targetCell = m_grid[x + (room.y * m_blueprint.m_gridWidth)];
                    if (targetCell == 0) { 
                        m_grid[x + (room.y * m_blueprint.m_gridWidth)] = getTileTypeFromLegend('c'); 
                    }
                }
            }

            void BasicLayoutGenerator::writeVerticalCorridor(coordinate room, coordinate midPoint) {

                // Ensure room is always above midPoint
                if (room.y > midPoint.y) {
                    std::swap(room, midPoint);
                }

                // Write vertical corridor
                for (int y = room.y; y <= midPoint.y; y++) {
                    ETileType targetCell = m_grid[room.x + (y * m_blueprint.m_gridWidth)];
                    if (targetCell == 0) {
                        m_grid[room.x + (y * m_blueprint.m_gridWidth)] = getTileTypeFromLegend('c'); 
                    }
                }
            }

        #pragma endregion

    #pragma endregion

#pragma endregion