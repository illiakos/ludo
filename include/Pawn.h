

#ifndef PAWN_H
#define PAWN_H

#include "Coordinates.h"
class Pawn {

public:
  Pawn(int id, int startingTile, Coordinates coordinates) : id(id), tileId(startingTile), coordinates(coordinates) {}
  const Coordinates& getCoordinates() const {return coordinates;}
  int getId() const {return id;}
  int getTileId() {return tileId;}
  int getPlayerId() const {return playerId;}
  int getTeamId() const {return teamId;}
  void setTileId(int tileId) {tileId = tileId;};
private:

  int teamId;
  int id;
  int playerId;
  Coordinates coordinates;
  int tileId;
};

#endif // !PAWN_H
