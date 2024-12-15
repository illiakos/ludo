#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Dimensions.hpp"
#include "Tile.hpp"
#include "Color.hpp"
class Board {
public:
    // Initialize the board with all tiles
    void initBoard();

    // Access a tile by its position
    const Tile* getTileByPosition(int position) const;

protected:
    // Add tiles of different types
    void addRegularTile(Dimensions d, int id, int position, Color& color);
    void addStartingTile(Dimensions d, int id, int position, Color& color);
    void addSafeTile(Dimensions d, int id, int position,Color& color);
    void addPrefinishingTile(Dimensions d, int id, int position, int firstFinishingTilePosition, Color& color);
    void addFinishingTile(Dimensions d, int id, int position, int indexInPath, int pathLength, Color& color);
    void sortTiles();
    void printBoard() const ;

private:
    // Store all tiles
    std::vector<std::unique_ptr<Tile>> tiles;
};

#endif // BOARD_H
