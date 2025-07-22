#pragma once
#include "GridBlueprint.h"

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
};
