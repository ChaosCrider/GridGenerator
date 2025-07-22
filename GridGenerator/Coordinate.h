#pragma once

struct coordinate
{
    /* data */
    int x, y = 0;

    coordinate(int x_, int y_)
        : x(x_), y(y_) {
    }
};
