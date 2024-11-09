#ifndef SIZE_H
#define SIZE_H

class Size {

public:
  Size(int width = 0, int height = 0) : width(width), height(height) {}
  int getWidth() { return width; }
  int getHeight() { return height; }

private:
  int width, height;
};

#endif // !
