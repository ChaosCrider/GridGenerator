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
	CorridorFloor, // floor in a corridor
	EntryPoint, // entry point tile
	EndPoint // end point tile
};

inline std::string to_string(ETileType tileType) {
    switch (tileType) {
    case empty:     return "_";
    case CornerWall:    return "l";
    case StraigthWall:     return "w";
    case InnerCornerWall:   return ".";
    case Door:     return "d";
    case WalledFloor:    return "f";
    case CornerWallFloor:   return "r";
    case InnerCornerWallFloor:  return "i";
    case RoomFloor:     return "r";
    case CorridorFloor:     return "c";
	case EntryPoint: return "="; // Entry point tile
	case EndPoint: return "#"; // End point tile
    default:    return "_";
    }
}

/*
    Legend:
    	x - empty tile
		r - room floor tile
		f - floor next to a straigth wall
		i - floor next to an corner wall
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
		case 'f': return ETileType::WalledFloor; // floor next to a straigth wall
		case 'i': return ETileType::InnerCornerWallFloor; // floor next to an internal wall
        case 'c': return ETileType::CorridorFloor; // corridor tile
        case 'w': return ETileType::StraigthWall; // wall tile
		case 'l': return ETileType::InnerCornerWall; // Inner Corner Wall
		case '.': return ETileType::CornerWall; // corner wall tile
	    case 'd': return ETileType::Door; // door tile
		case '=': return ETileType::EntryPoint; // Entry point tile
		case '#': return ETileType::EndPoint; // End point tile
    }
    return empty; // Default case
}