#pragma once

#include <string>

enum ETileType {
    empty, // empty tile
    CornerWall, // corner wall
    StraigthWall, // straight wall
    InnerCornerWall, // inner corner wall
    Door, // door
    WalledFloor, // floor next to a straigth floor
    CornerWallFloor, // floor next to a corner wall
    InnerCornerWallFloor, // floor next to an intrernal wall floor
    RoomFloor, // floor surounded by other floor
	CorridorFloor // floor in a corridor
};

inline std::string to_string(ETileType tileType) {
    switch (tileType) {
    case empty:     return "_";
    case CornerWall:    return "w";
    case StraigthWall:     return "w";
    case InnerCornerWall:   return "w";
    case Door:     return "d";
    case WalledFloor:    return "r";
    case CornerWallFloor:   return "r";
    case InnerCornerWallFloor:  return "r";
    case RoomFloor:     return "r";
    case CorridorFloor:     return "c";
    default:    return "_";
    }
}

/*
    Legend:
    	x - empty tile
		r - room floor tile
        c - corridor tile
        w - wall tile
		l - Inner Corner Wall
		. - corner wall tile
		d - door tile
*/
inline ETileType getTileTypeFromLegend(const char index) {
    switch (index) {
	    case 'x': return ETileType::empty;
	    case 'r': return ETileType::RoomFloor; // room floor tile
        case 'c': return ETileType::CorridorFloor; // corridor tile
        case 'w': return ETileType::StraigthWall; // wall tile
		case 'l': return ETileType::InnerCornerWall; // Inner Corner Wall
		case '.': return ETileType::CornerWall; // corner wall tile
	    case 'd': return ETileType::Door; // door tile
    }
    return empty; // Default case
}