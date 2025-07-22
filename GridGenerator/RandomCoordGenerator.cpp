#pragma once

#include <random>
#include <utility>
#include "RandomCoordGenerator.h"
#include "Coordinate.h"


RandomCoordGenerator::RandomCoordGenerator()
    : m_gen(std::random_device{}())
{
}

int RandomCoordGenerator::getRandomInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(m_gen);
}

// meant to generate the first coordinate of a room
coordinate RandomCoordGenerator::getRandomCoord(int xMin, int xMax, int yMin, int yMax) {
    std::uniform_int_distribution<> xDist(xMin, xMax);
    std::uniform_int_distribution<> yDist(yMin, yMax);
    int x(xDist(m_gen));
    int y(yDist(m_gen));
    return coordinate(x, y);
}

// meant to generate the second coordinate of a room
// change so it take in the 1st point of a room, and uses x and y values ranges to create the second point.
coordinate RandomCoordGenerator::getRandomCoord(coordinate startingPoint, std::pair<int, int> roomWidth, std::pair<int, int> roomHeight)
{
    std::uniform_int_distribution<> xDist(startingPoint.x + roomWidth.first, startingPoint.x + roomWidth.second);
    std::uniform_int_distribution<> yDist(startingPoint.y + roomWidth.first, startingPoint.y + roomWidth.second);
    int x(xDist(m_gen));
    int y(yDist(m_gen));
    return coordinate(x, y);
}
