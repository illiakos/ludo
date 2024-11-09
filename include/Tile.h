

#ifndef TILE_H
#define TILE_H
#include "Color.h"
#include "Coordinates.h"
#include "Size.h"


class Tile {
public:
    Tile(int x, int y, int id, int position, Color& color, Size size)
        : coordinates(x, y), id(id), position(position), color(color) {}

    Tile(int x, int y, int z, int id, int position, Color& color, Size size)
        : coordinates(x, y, z), id(id), position(position), color(color), size(size) {}

    // Accessors
    const Coordinates& getCoordinates() const { return coordinates; }
    int getId() const { return id; }
    int getPosition() const { return position; }

    // Comparison operator to sort by position
    bool operator<(const Tile& other) const {
        return position < other.position;
    }
    virtual ~Tile() = default;

private:
    Coordinates coordinates; // Encapsulated coordinates (supports 2D and 3D)
    int id; // Unique identifier for the tile
    int position; // Position in the game flow, used for sorting
    Color color;
    Size size;
};

#endif // ! TILE_H
