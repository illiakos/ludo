#include "Board.h"
#include "SpecialTiles.h"
#include "Size.h"
#include <algorithm>
#include <iostream>
#include <memory>

// Add regular tile
void Board::addRegularTile(int x, int y, int id, int position, Color& color, Size size) {
    tiles.push_back(std::make_unique<Tile>(x, y, id, position, color, size));
}

// Add safe tile
void Board::addSafeTile(int x, int y, int id, int position, Color& color, Size size) {
    tiles.push_back(std::make_unique<SafeTile>(x, y, id, position, color, size));
}

// Add starting tile
void Board::addStartingTile(int x, int y, int id, int position, Color& color, Size size) {
    tiles.push_back(std::make_unique<StartingTile>(x, y, id, position, color, size));
}

// Add prefinishing tile
void Board::addPrefinishingTile(int x, int y, int id, int position, int firstFinishingTilePosition, Color& color, Size size) {
    auto tile = std::make_unique<PrefinishingTile>(x, y, id, position,firstFinishingTilePosition, color, size);
    tile->setFirstFinishingTilePosition(firstFinishingTilePosition);
    tiles.push_back(std::move(tile));
}

// Add finishing tile
void Board::addFinishingTile(int x, int y, int id, int position, Size size, int indexInPath, int pathLength, Color& color) {
    tiles.push_back(std::make_unique<FinishingTile>(x, y, id, position, color, size, indexInPath == (pathLength - 1)));
}

// Get tile by position
const Tile* Board::getTileByPosition(int position) const {
    for (const auto& tile : tiles) {
        if (tile->getPosition() == position) {
            return tile.get();
        }
    }
    return nullptr;
}

// Sort tiles by position
void Board::sortTiles() {
    std::sort(tiles.begin(), tiles.end(),
        [](const std::unique_ptr<Tile>& a, const std::unique_ptr<Tile>& b) {
            return a->getPosition() < b->getPosition();
        });
}

// Print the board (for debugging)
void Board::printBoard() const {
    for (const auto& tile : tiles) {
        const auto& coords = tile->getCoordinates();
        std::cout << "Tile ID: " << tile->getId() << " at (" << coords.getX()
                  << ", " << coords.getY() << "), Position: " << tile->getPosition() << "\n";
    }
}
