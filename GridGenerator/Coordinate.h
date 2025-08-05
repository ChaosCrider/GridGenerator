#pragma once
#include "GridBlueprint.h"
#include <string>

struct coordinate
{
    /* data */
    int x, y = 0;

    coordinate(int x_, int y_)
        : x(x_), y(y_) {
    }

    int getIndex(GridBlueprint blueprint) {
        return (y * blueprint.m_gridWidth) + x;
    }

    std::string toString(){
            return "Coordinate(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    };
};


// startRoom - ID = int
// endRoom - ID = int
// length = int
struct corridor {
    int startRoom; // Room id for the start point of the corridor
    int endRoom;   // Room id for the end point of the corridor
    int length; // Length of the corridor
};

