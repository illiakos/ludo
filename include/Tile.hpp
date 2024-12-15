

#ifndef TILE_H
#define TILE_H
#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
#include <string>

class Tile: public Renderable {
public:

    Tile(Dimensions dimensions,int id, int position, Color& color)
        : dimensions(dimensions), id(id), position(position), color(color) {}

    // Accessors
    Dimensions getDimensions();
    int getId() const;
    int getPosition() const;

    // Comparison operator to sort by position
    bool operator<(const Tile& other) const {
        return position < other.position;
    }
    virtual ~Tile() = default;
    void renderSelf() const override;
    std::string toString();


private:
    int id; // Unique identifier for the tile
    int position; // Position in the game flow, used for sorting
    Color color;

    Dimensions dimensions;
};

#endif // ! TILE_H
