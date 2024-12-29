

#ifndef TILE_H
#define TILE_H
#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
#include "TileContext.hpp"
#include <string>


class Tile : public Renderable {
public:
  Tile(Dimensions dimensions, int id, int position, Color color,
       int teamId = -1)
      : dimensions(dimensions), teamId(teamId), id(id), position(position),
        color(color) {}

  Tile(Dimensions dimensions, int id, int position, Color color,TileContext context,
       int teamId = -1)
      : dimensions(dimensions), teamId(teamId), id(id), position(position),context(context),
        color(color) {}

  void setContext(TileContext newContext) { context = newContext; }
  void setTeamId(int newTeamId) { teamId = newTeamId; }
  // Accessors
  Dimensions getDimensions();
  int getId() const;
  int getPosition() const;
  TileContext getContext();

  // Comparison operator to sort by position
  bool operator<(const Tile &other) const { return position < other.position; }
  virtual ~Tile() = default;
  virtual void renderSelf() const override;
  std::string toString();
protected:
  int id;       // Unique identifier for the tile
  int position; // Position in the game flow, used for sorting
  Color color;
  TileContext context;
  int teamId;
  Dimensions dimensions;
  
  std::string contextToString(TileContext context) const ;
};

#endif // ! TILE_H
