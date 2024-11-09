#ifndef SPECIAL_TILES_H
#define SPECIAL_TILES_H

#include "Tile.h"
class StartingTile : public Tile {
public:
  StartingTile(int x, int y, int id, int position, Color &color)
      : Tile(x, y, id, position, color) {}
  StartingTile(int x, int y, int z, int id, int position, Color &color)
      : Tile(x, y, z, id, position, color) {}
};

class FinishingTile : public Tile {
public:
  FinishingTile(int x, int y, int id, int position, Color &color, bool isFinish)
      : Tile(x, y, id, position, color), isFinish(isFinish) {}
  FinishingTile(int x, int y, int z, int id, int position, Color &color, bool isFinish)
      : Tile(x, y, z, id, position, color), isFinish(isFinish) {}

  bool getIsFinish() {return isFinish;}

private:
  bool isFinish;
};



class PrefinishTile : public Tile {
public:
  PrefinishTile(int x, int y, int id, int position, Color &color)
      : Tile(x, y, id, position, color) {}

  PrefinishTile(int x, int y, int z, int id, int position, Color &color)
      : Tile(x, y, z, id, position, color) {}
  int getFirstFinishingTilePosition() const { return firstFinishingTilePosition;}
  
protected:
  int firstFinishingTilePosition;
};

class SafeTile : public Tile {
public:
  
  SafeTile (int x, int y, int id, int position, Color &color)
      : Tile(x, y, id, position, color) {}

  SafeTile (int x, int y, int z, int id, int position, Color &color)
      : Tile(x, y, z, id, position, color) {}
};

#endif // !SPECIAL_TILES_H
