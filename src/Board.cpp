#include "Board.h"
#include "SpecialTiles.h"
#include <algorithm>
#include <iostream>
#include <memory>

void Board::addRegularTile(int x, int y, int id, int position, Color& color, Size size) {
    tiles.push_back(std::make_unique<Tile>(x, y, id, position, color, size));
}

void Board::addSafeTile(int x, int y, int id, int position, Color& color, Size size) {
    tiles.push_back(std::make_unique<SafeTile>(x, y, id, position, color, size));
}

void Board::addPrefinishingTile(int x, int y, int id, int position, Color& color, Size size, int finishingStartPosition) {
    auto tile = std::make_unique<PrefinishTile>(x, y, id, position, color, size);
    tile->firstFinishingTilePosition = finishingStartPosition;
    tiles.push_back(std::move(tile));
}

void Board::addFinishingTile(int x, int y, int id, int position, Color& color, Size size, bool isFinish) {
    tiles.push_back(std::make_unique<FinishingTile>(x, y, id, position, color, size, isFinish));
}

const Tile* Board::getTileByPosition(int position) const {
    for (const auto& tile : tiles) {
        if (tile->getPosition() == position) {
            return tile.get();
        }
    }
    return nullptr;
}

void Board::sortTiles() {
    std::sort(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& a, const std::unique_ptr<Tile>& b) {
        return a->getPosition() < b->getPosition();
    });
}

void Board::printBoard() const {
    for (const auto& tile : tiles) {
        const auto& coords = tile->getCoordinates();
        std::cout << "Tile ID: " << tile->getId()
                  << " at (" << coords.getX() << ", " << coords.getY() << ", " << coords.getZ() 
                  << "), Position: " << tile->getPosition() << "\n";
    }
}
