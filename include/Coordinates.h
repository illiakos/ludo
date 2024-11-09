

#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates {
public:
    // Constructors for 2D and 3D
    Coordinates(int x, int y, int z = 0) : x(x), y(y), z(z) {}

    // Accessors
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }

    // Equality check for comparisons
    bool operator==(const Coordinates& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

private:
    int x, y, z; // Coordinates in 2D or 3D space
};

#endif // !COORDINATES_H
