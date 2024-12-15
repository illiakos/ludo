

#ifndef PAWN_H
#define PAWN_H

#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
class Pawn : public Renderable {

public:
  Pawn(int id, int startingTile, Dimensions dimensions, Color& color) : id(id), tileId(startingTile), dimensions(dimensions), color(color) {}
  const Dimensions& getDimensions() const {return dimensions;}
  int getId() const {return id;}
  int getTileId() {return tileId;}
  int getPlayerId() const {return playerId;}
  int getTeamId() const {return teamId;}
  void setTileId(int tileId) {tileId = tileId;};
 
  void renderSelf() const override;

private:
  Dimensions dimensions;
  int teamId;
  int id;
  int playerId;
  Color color;
  /*Coordinates coordinates;*/
  int tileId;
};

#endif // !PAWN_H
