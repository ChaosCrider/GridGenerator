#pragma once

#include <random>
#include <utility>
#include "Coordinate.h"

class RandomCoordGenerator {

private:
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_dist;

public:
    RandomCoordGenerator();
    int getRandomInt(int min, int max);
    coordinate getRandomCoord(int xMin, int xMax, int yMin, int yMax);
    coordinate getRandomCoord(coordinate startingPoint, std::pair<int, int> roomWidth, std::pair<int, int> roomHeight);

};