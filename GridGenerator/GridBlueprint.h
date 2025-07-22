#pragma once

struct GridBlueprint
{
    /* data */
    int m_gridWidth;
    int m_gridHeight;
    int m_roomMinSize;
    int m_roomMaxSize;
    int m_gridEdgeBuffer;
    int m_roomCount;

    GridBlueprint()
        : m_gridWidth(0), m_gridHeight(0), m_roomMinSize(0),
        m_roomMaxSize(0), m_gridEdgeBuffer(0), m_roomCount(0)
    {

    }
    GridBlueprint(int gridwidth, int gridHeight, int roomMinSize, int roomMaxSize, int gridEdgeBuffer, int roomcount)
        : m_gridWidth(gridwidth), m_gridHeight(gridHeight), m_roomMinSize(roomMinSize),
        m_roomMaxSize(roomMaxSize), m_gridEdgeBuffer(gridEdgeBuffer), m_roomCount(roomcount) {
    }
};
