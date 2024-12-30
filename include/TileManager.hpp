#ifndef TILE_MANAGER_HPP
#define TILE_MANAGER_HPP

#include "Renderable.hpp"
#include "Tile.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

enum PositionType {

};

class TileManager {

public:
  static TileManager &getInstance ();

  void addTile (std::shared_ptr<Tile> tile);
  std::shared_ptr<Tile> findTileById (int id) const;

  void addWalkableTile (std::shared_ptr<Tile> tile);
  void addBaseTile (std::shared_ptr<Tile> tile);

  const std::vector<std::shared_ptr<Tile>> &getWalkableTiles () const;
  const std::vector<std::shared_ptr<Tile>> &getBaseTiles () const;
  void printTiles () const;
  std::shared_ptr<Tile> findTileByContextAndPosition (TileContext context, int position);

private:
  RenderableContainer &renderContainer;

  // Unified storage of tiles by ID
  std::unordered_map<int, std::shared_ptr<Tile>> tiles;

  // Separate containers for categories (store references or IDs)
  std::vector<std::shared_ptr<Tile>> walkableTiles;
  std::vector<std::shared_ptr<Tile>> baseTiles;

  TileManager (RenderableContainer &renderContainer) : renderContainer (renderContainer) {}
  TileManager (const TileManager &) = delete;
  TileManager &operator= (const TileManager &) = delete;
};

#endif // !TILE_MANAGER_HPP
