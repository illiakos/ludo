#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Tile.h"
#include "Color.h"
class Board {
public:
    // Initialize the board with all tiles
    void initBoard();

    // Access a tile by its position
    const Tile* getTileByPosition(int position) const;

protected:
    // Add tiles of different types
    void addRegularTile(int x, int y, int id, int position, Color& color, Size size);
    void addStartingTile(int x, int y, int id, int position, Color& color, Size size);
    void addSafeTile(int x, int y, int id, int position,Color& color, Size size);
    void addPrefinishingTile(int x, int y, int id, int position, int firstFinishingTilePosition, Color& color, Size size);
    void addFinishingTile(int x, int y, int id, int position, Size size, int indexInPath, int pathLength, Color& color);
    void sortTiles();
    void printBoard() const ;

private:
    // Store all tiles
    std::vector<std::unique_ptr<Tile>> tiles;
};

#endif // BOARD_H
