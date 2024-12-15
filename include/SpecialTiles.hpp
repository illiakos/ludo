#ifndef SPECIAL_TILES_H
#define SPECIAL_TILES_H

#include "Dimensions.hpp"
#include "Tile.hpp"
class StartingTile : public Tile {
public:
    StartingTile(Dimensions dimensions, int id, int position, Color& color)
        : Tile(dimensions, id, position, color) {};

    void renderSelf() const override;
};

class FinishingTile : public Tile {
public:
    FinishingTile(Dimensions dimensions, int id, int position, Color& color, bool isFinish)
        : Tile(dimensions, id, position, color), isFinish(isFinish) {};

    bool getIsFinish();
    void renderSelf() const override;

private:
    bool isFinish;
};



class PrefinishingTile : public Tile {
public:
    PrefinishingTile(Dimensions d, int id, int position, int nextPosition, Color& color)
      : Tile(d, id, position, color), nextPosition(nextPosition) {};
    
    int getNextPosition();
    void setFirstFinishingTilePosition(int pos);
    int getFirstFinishingTilePosition();
    int getTeamId();
    void renderSelf() const override;
private:
    int teamId;
    int nextPosition; // Position of the next tile in the prefinishing path
    int firstFinishingTilePosition;
};

class SafeTile : public Tile {
public:
    SafeTile(Dimensions d, int id, int position, Color& color)
        : Tile(d, id, position, color) {};
    void renderSelf() const override;
};

#endif // !SPECIAL_TILES_H
