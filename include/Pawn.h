#ifndef PAWN_H
#define PAWN_H

class Pawn {
public:
  Pawn();
  void move(int toSquareID);
  int getSquare();

private:
  int square_id;
};

#endif
