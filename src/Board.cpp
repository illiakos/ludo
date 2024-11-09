#include "Board.h"
#include <algorithm>
#include <iostream>

void Board::addRegularTile(int x, int y, int id, int position) {
    tiles.push_back(std::make_unique<Tile>(x, y, id, position));
}

void Board::addSafeTile(int x, int y, int id, int position) {
    tiles.push_back(std::make_unique<SafeTile>(x, y, id, position));
}

void Board::addPrefinishingTile(int x, int y, int id, int position, int finishingStartPosition) {
    tiles.push_back(std::make_unique<PrefinishingTile>(x, y, id, position, finishingStartPosition));
}

void Board::addFinishingTile(int x, int y, int id, int position, int indexInPath, int pathLength) {
    tiles.push_back(std::make_unique<FinishingTile>(x, y, id, position, indexInPath, pathLength));
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
    std::sort(tiles.begin(), tiles.end());
}

void Board::printBoard() const {
    for (const auto& tile : tiles) {
        const auto& coords = tile.getCoordinates();
        std::cout << "Tile ID: " << tile.getId() << " at (" << coords.getX()
                  << ", " << coords.getY() << ", " << coords.getZ() << "), Position: "
                  << tile.getPosition() << "\n";
    }
}
