#ifndef DIMENSIONS_H
#define DIMENSIONS_H

class Dimensions {
public:
  int x;
  int y;
  

  int dx; // Alternatively width
  int dy; // Alternatively height

  // Optional parameters
  int z;
  int dz;

  Dimensions(int x, int y, int dx, int dy) : x(x), y(y), dx(dx), dy(dy) {};

};

#endif // !DIMENSIONS_H
