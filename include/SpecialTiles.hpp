#ifndef SPECIAL_TILES_H
#define SPECIAL_TILES_H

#include "Dimensions.hpp"
#include "Tile.hpp"
#include "TileContext.hpp"
class StartingTile : public Tile {
public:
    StartingTile(Dimensions dimensions, int id, int position, Color& color, int teamId)
        : Tile(dimensions, id, position, color), teamId(teamId) {};

    void renderSelf() const override;
    ~StartingTile();
private:
  int teamId;
};

class FinishingTile : public Tile {
public:
    FinishingTile(Dimensions dimensions, int id, int position, Color& color, bool isFinish)
        : Tile(dimensions, id, position, color), isFinish(isFinish) {};

    bool getIsFinish();
    void renderSelf() const override;
    ~FinishingTile();

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
    ~PrefinishingTile();
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
    ~SafeTile();
};

class TransitionTile : public Tile {
public:
    TransitionTile(Dimensions dimensions, int id, int position, int teamId, int finishingTileStartPosition, Color& color)
        : Tile(dimensions, id, position, color, TileContext::Walkable),
          teamId(teamId), finishingTileStartPosition(finishingTileStartPosition) {}

    int getTeamId() const { return teamId; }
    int getFinishingTileStartPosition() const { return finishingTileStartPosition; }
    ~TransitionTile();
    void renderSelf() const override;
private:
    int teamId;
    int finishingTileStartPosition; // Position in Finishing context to start
};

#endif // !SPECIAL_TILES_H
