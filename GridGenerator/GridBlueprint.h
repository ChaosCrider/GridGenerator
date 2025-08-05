#pragma once

/// <summary>
/// Blueprint for generating a grid layout.
/// int m_gridWidth;
/// int m_gridHeight;
/// int m_roomMinSize;
/// int m_roomMaxSize;
/// int m_gridEdgeBuffer;
/// int m_roomCount;
/// </summary>

/*
int m_gridWidth;
int m_gridHeight;
int m_roomMinSize;
int m_roomMaxSize;
int m_gridEdgeBuffer;
int m_roomCount;
*/
struct GridBlueprint
{
    /// <summary>
	/// Width of the grid.
	/// </summary>
    int m_gridWidth;

    /// <summary>
    /// Represents the height of a grid.
    /// </summary>
    int m_gridHeight;

    /// <summary>
    /// Stores the minimum allowed size for a room.
    /// </summary>
    int m_roomMinSize;

    /// <summary>
    /// Stores the maximum size of a room.
    /// </summary>
    int m_roomMaxSize;

    /// <summary>
    /// Stores the buffer size at the edge of a grid.
    /// </summary>
    int m_gridEdgeBuffer;

    /// <summary>
    /// Stores the number of rooms.
    /// </summary>
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
