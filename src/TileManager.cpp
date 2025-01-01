#include "TileManager.hpp"
#include "MapDrawer.hpp"
#include "Renderable.hpp"
#include "SpecialTiles.hpp"
#include <iostream>
#include <memory>
#include <ostream>

TileManager &TileManager::getInstance () {
  static TileManager instance (MapDrawer::getInstance ());
  return instance;
}

void TileManager::addTile (std::shared_ptr<Tile> tile) {
  tiles[tile->getId ()] = tile;
}

std::shared_ptr<Tile> TileManager::findTileById (int id) const {
  auto it = tiles.find (id);
  if (it != tiles.end ()) {
    return it->second;
  }
  return nullptr; // Tile not found
}

void TileManager::printTiles() const {
  // Create a vector to hold the tiles for sorting
  std::vector<std::shared_ptr<Tile>> sortedTiles;

  // Extract tiles from the map into the vector
  for (const auto &[id, tile] : tiles) {
    sortedTiles.push_back(tile);
  }

  // Sort the vector based on tile IDs
  std::sort(sortedTiles.begin(), sortedTiles.end(),
            [](const std::shared_ptr<Tile> &a, const std::shared_ptr<Tile> &b) {
              return a->getId() < b->getId();
            });

  // Print the sorted tiles
  for (const auto &tile : sortedTiles) {
    std::cout << "Tile ID: " << tile->getId() << " -> " << tile->toString() << std::endl;
  }
}
const std::vector<std::shared_ptr<Tile>> &TileManager::getWalkableTiles () const {
  return walkableTiles;
}

const std::vector<std::shared_ptr<Tile>> &TileManager::getBaseTiles () const {
  return baseTiles;
}

std::shared_ptr<Tile> TileManager::findTileByContextAndPosition (
    TileContext context, int position) {
  for (const auto &[id, tile] : tiles) { // Use structured binding to unpack key-value pairs

    if (tile->getContext () == context && tile->getPosition () == position) {
      return tile;
    }
  }
  return nullptr; // Tile not found
}


std::shared_ptr<PrefinishingTile> TileManager::findPrefinishingTileByContextPositionAndTeam(
    TileContext context, int position, int teamId) {
  // Iterate through the tiles
  for (const auto &[id, tile] : tiles) { // Use structured binding to unpack key-value pairs
    // Check context and position
    if (tile->getContext() == context && tile->getPosition() == position) {
      // Attempt to downcast to PrefinishingTile
      auto prefinishingTile = std::dynamic_pointer_cast<PrefinishingTile>(tile);

      std::cout << "found similar tile : " << prefinishingTile->toString()  <<endl;
      if (prefinishingTile && prefinishingTile->getTeamId() == teamId) {
        return prefinishingTile; // Return the matching PrefinishingTile
      }
    }
  }
  return nullptr; // Return nullptr if no matching PrefinishingTile is found
}

