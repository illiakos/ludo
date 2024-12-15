#ifndef BASE_H
#define BASE_H

#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
#include "Tile.hpp"
#include <vector>
class Base : public Renderable {

public:
  Base(Dimensions dimensions, Color color, int teamId, int startingTileId ) : dimensions(dimensions), color(color), teamId(teamId), startingTileId(startingTileId) {};
  void renderSelf() const override;
private:
  std::vector<Tile*> slots;
  Dimensions dimensions;
  Color color;
  int teamId;
  int startingTileId;
};

#endif // !BASE_H
