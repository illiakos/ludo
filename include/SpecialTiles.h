#ifndef SPECIAL_TILES_H
#define SPECIAL_TILES_H

#include "Tile.h"
class StartingTile : public Tile {
public:
    StartingTile(int x, int y, int id, int position, Color& color, Size size)
        : Tile(x, y, id, position, color, size) {}

    StartingTile(int x, int y, int z, int id, int position, Color& color, Size size)
        : Tile(x, y, z, id, position, color, size) {}
};

class FinishingTile : public Tile {
public:
    FinishingTile(int x, int y, int id, int position, Color& color, Size size, bool isFinish)
        : Tile(x, y, id, position, color, size), isFinish(isFinish) {}

    FinishingTile(int x, int y, int z, int id, int position, Color& color, Size size, bool isFinish)
        : Tile(x, y, z, id, position, color, size), isFinish(isFinish) {}

    bool getIsFinish() const { return isFinish; }

private:
    bool isFinish;
};



class PrefinishingTile : public Tile {
public:
    PrefinishingTile(int x, int y, int id, int position, int nextPosition, Color& color, Size size)
      : Tile(x, y, id, position, color, size), nextPosition(nextPosition) {}
    
    PrefinishingTile(int x, int y, int z, int id, int position, int nextPosition, Color& color, Size size)
      : Tile(x, y, z, id, position, color, size), nextPosition(nextPosition) {}

    int getNextPosition() const { return nextPosition; }

private:
    int nextPosition; // Position of the next tile in the prefinishing path
};

class SafeTile : public Tile {
public:
    SafeTile(int x, int y, int id, int position, Color& color, Size size)
        : Tile(x, y, id, position, color, size) {}

    SafeTile(int x, int y, int z, int id, int position, Color& color, Size size)
        : Tile(x, y, z, id, position, color, size) {}
};

#endif // !SPECIAL_TILES_H
