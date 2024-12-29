#include "TileManager.hpp"
#include "MapDrawer.hpp"
#include "Renderable.hpp"
#include <iostream>
#include <memory>
#include <ostream>

TileManager &TileManager::getInstance() {
  static TileManager instance(MapDrawer::getInstance());
  return instance;
}

void TileManager::addTile(std::shared_ptr<Tile> tile) {
  tiles[tile->getId()] = tile;

}

std::shared_ptr<Tile> TileManager::findTileById(int id) const {
  auto it = tiles.find(id);
  if (it != tiles.end()) {
    return it->second;
  }
  return nullptr; // Tile not found
}

void TileManager::printTiles() const {
  for (const auto &[id, tile] : tiles) {
    std::cout << "Tile ID: " << id << " -> " << tile->toString() << std::endl;
  }
}
const std::vector<std::shared_ptr<Tile>> &
TileManager::getWalkableTiles() const {
  return walkableTiles;
}

const std::vector<std::shared_ptr<Tile>> &TileManager::getBaseTiles() const {
  return baseTiles;
}

std::shared_ptr<Tile> TileManager::findTileByContextAndPosition(TileContext context, int position)  {
    for (const auto& [id, tile] : tiles) { // Use structured binding to unpack key-value pairs
        
        if (tile->getContext() == context && tile->getPosition() == position) {
            return tile;
        }
    }
    return nullptr; // Tile not found
}
