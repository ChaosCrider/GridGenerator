#pragma once

enum eTileType {
x, // empty tile
cw, // corner wall
w, // straight wall
icw, // inner corner wall
d, // door
wf, // floor next to a straigth floor
cwf, // floor next to a corner wall
icwf, // floor next to an intrernal wall floor
f // floor surounded by other floor
};