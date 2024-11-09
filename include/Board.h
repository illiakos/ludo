#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"

class Board {
public:
    const Tile* getTileByPosition(int position) const;

protected:

    void addRegularTile(int x, int y, int id, int position);
    void addSafeTile(int x, int y, int id, int position);
    void addPrefinishingTile(int x, int y, int id, int position, int finishingStartPosition);
    void addFinishingTile(int x, int y, int id, int position, int indexInPath, int pathLength);


private:
    std::vector<std::unique_ptr<Tile>> tiles;
    
};

#endif // BOARD_H
