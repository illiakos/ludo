

#ifndef PAWN_H
#define PAWN_H

#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
#include "TileContext.hpp"

class Pawn : public Renderable {

public:
  Pawn(int id, int startingTile, int teamId, Dimensions dimensions,
       Color &color)
      : id(id), tileId(startingTile), dimensions(dimensions), teamId(teamId),
        color(color), active(true) {
    setZIndex(2);
  }
  const Dimensions &getDimensions() const override { return dimensions; }
  int getId() const { return id; }
  int getTileId() { return tileId; }
  int getPlayerId() const { return playerId; }
  int getTeamId() const { return teamId; }
  void setTileId(int t) { tileId = t; };

  void renderSelf() const override;

  TileContext getContext();
  void setContext(TileContext context);
  void setDimensions(Dimensions d) const ;
  bool isActive();
  void setActive(bool active);
  void onClick() override;

  // Getter for z-index
  int getZIndex() const override { return zIndex; };

  // Setter for z-index
  void setZIndex(int z) override { zIndex = z; };

private:
  mutable Dimensions dimensions;
  int teamId;
  int id;
  int playerId;
  int zIndex = 2;
  Color color;
  TileContext context;
  bool active = true;
  int tileId;
};

#endif // !PAWN_H
