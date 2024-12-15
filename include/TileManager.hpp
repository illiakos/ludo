#ifndef TILE_MANAGER_HPP
#define TILE_MANAGER_HPP


#include "Renderable.hpp"
#include "Tile.hpp"
#include <memory>
#include <vector>

class TileManager {

public:

  static TileManager& getInstance();
  void addTile(Tile tile);
  void printTiles();


private:
  RenderableContainer renderContainer;
  TileManager() = default;
  std::vector<std::shared_ptr<Tile>> tiles;
};

#endif // !TILE_MANAGER_HPP
