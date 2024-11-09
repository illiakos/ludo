

#ifndef PAWN_H
#define PAWN_H

#include "Coordinates.h"
class Pawn {

public:
  const Coordinates& getCoordinates() const {return coordinates;}
  int getId() const {return id;}
  int getTileId() {return tileId;}
  int getPlayerId() const {return playerId;}

private:

  int id;
  int playerId;
  Coordinates coordinates;
  int tileId;
};

#endif // !PAWN_H
