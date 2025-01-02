#ifndef DIMENSIONS_H
#define DIMENSIONS_H
#include <iostream>

class Dimensions {
public:
  int x;
  int y;

  float dx; // Alternatively width
  float dy; // Alternatively height

  // Optional parameters
  int z;
  int dz;

  // Converts grid coordinates (0-15) to OpenGL coordinates
  std::pair<float, float> gridToOpenGL(int x, int y,
                                       const Dimensions &gridDimensions);

  Dimensions(int x, int y, float dx, float dy) : x(x), y(y), dx(dx), dy(dy) {};
  friend std::ostream &operator<<(std::ostream &os, const Dimensions &d) {
    os << "Dimensions: { x: " << d.x << ", y: " << d.y
       << ", dx (width): " << d.dx << ", dy (height): " << d.dy
       << ", z: " << d.z << ", dz: " << d.dz << " }";
    return os;
  }
};

#endif // !DIMENSIONS_H
