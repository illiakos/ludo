#include "Board.hpp"
#include "Dimensions.hpp"
#include "SpecialTiles.hpp"
#include <algorithm>
#include <iostream>
#include <memory>

// Add regular tile
void Board::addRegularTile(Dimensions d, int id, int position, Color &color) {
  tiles.push_back(std::make_unique<Tile>(d, id, position, color));
}

// Add safe tile
void Board::addSafeTile(Dimensions d, int id, int position, Color &color) {
  tiles.push_back(std::make_unique<SafeTile>(d, id, position, color));
}

// Add starting tile
void Board::addStartingTile(Dimensions d, int id, int position, Color &color) {
  tiles.push_back(std::make_unique<StartingTile>(d, id, position, color));
}

// Add prefinishing tile
void Board::addPrefinishingTile(Dimensions d, int id, int position,
                                int firstFinishingTilePosition, Color &color) {
  auto tile = std::make_unique<PrefinishingTile>(
      d, id, position, firstFinishingTilePosition, color);
  tile->setFirstFinishingTilePosition(firstFinishingTilePosition);
  tiles.push_back(std::move(tile));
}

// Add finishing tile
void Board::addFinishingTile(Dimensions d, int id, int position,
                             int indexInPath, int pathLength, Color &color) {
  tiles.push_back(std::make_unique<FinishingTile>(
      d, id, position, color, indexInPath == (pathLength - 1)));
}

// Get tile by position
const Tile *Board::getTileByPosition(int position) const {
  for (const auto &tile : tiles) {
    if (tile->getPosition() == position) {
      return tile.get();
    }
  }
  return nullptr;
}

// Sort tiles by position
void Board::sortTiles() {
  std::sort(tiles.begin(), tiles.end(),
            [](const std::unique_ptr<Tile> &a, const std::unique_ptr<Tile> &b) {
              return a->getPosition() < b->getPosition();
            });
}

// Print the board (for debugging)
void Board::printBoard() const {
  for (const auto &tile : tiles) {
    const auto &coords = tile->getDimensions();
    std::cout << "Tile ID: " << tile->getId() << " at (" << coords.x << ", "
              << coords.y << "), Position: " << tile->getPosition() << "\n";
  }
}
