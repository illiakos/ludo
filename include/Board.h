#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include "Tile.h"

class Board {
public:
    const Tile* getTileByPosition(int position) const;

    void sortTiles();       // Sort tiles by position
    void printBoard() const; // Print information about all tiles

protected:
    void addRegularTile(int x, int y, int id, int position, Color& color, Size size);
    void addSafeTile(int x, int y, int id, int position, Color& color, Size size);
    void addPrefinishingTile(int x, int y, int id, int position, Color& color, Size size, int finishingStartPosition);
    void addFinishingTile(int x, int y, int id, int position, Color& color, Size size, bool isFinish);

private:
    std::vector<std::unique_ptr<Tile>> tiles;
};
#endif // BOARD_H
