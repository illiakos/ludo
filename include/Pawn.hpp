

#ifndef PAWN_H
#define PAWN_H

#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
#include "TileContext.hpp"

class Pawn : public Renderable {

public:
  Pawn (int id, int startingTile, int teamId, Dimensions dimensions, Color &color)
      : id (id), tileId (startingTile), dimensions (dimensions), teamId (teamId), color (color), active(true) {}
  const Dimensions &getDimensions () const { return dimensions; }
  int getId () const { return id; }
  int getTileId () { return tileId; }
  int getPlayerId () const { return playerId; }
  int getTeamId () const { return teamId; }
  void setTileId (int t) { tileId = t; };

  void renderSelf () const override;

  TileContext getContext ();
  void setContext (TileContext context);
  void setDimensions (Dimensions d);
  bool isActive();
  void setActive(bool active);

private:
  Dimensions dimensions;
  int teamId;
  int id;
  int playerId;
  Color color;
  TileContext context;
  /*Coordinates coordinates;*/
  bool active = true;
  int tileId;
};

#endif // !PAWN_H
