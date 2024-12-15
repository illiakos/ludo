#include "TileManager.hpp"
#include "Renderable.hpp"
#include <iostream>
#include <memory>
#include <ostream>

TileManager& TileManager::getInstance() {
  static TileManager instance;
  return instance;
}

void TileManager::addTile(Tile tile) {
    auto tilePtr = std::make_shared<Tile>(tile);

    tiles.push_back(tilePtr);

    renderContainer.addRenderable(tilePtr);
}

void TileManager::printTiles() {
  for(auto tile : tiles) {
    std::cout << tile->toString() << std::endl;
  }
}


