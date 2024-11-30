#ifndef PAWN_MANAGER_H
#define PAWN_MANAGER_H

#include "Pawn.h"
#include <memory>
#include <unordered_map>

class PawnManager {
public:
  void addPawn(int pawnId, int startingTileId);
  void movePawn(int pawnId, int newTileId);

  // Methods updated to work with pawnId only
  std::shared_ptr<Pawn> getPawn(int pawnId) const;
  int getPawnTileId(int pawnId) const;
  bool hasPawnAtTile(int tileId) const;
  std::shared_ptr<Pawn>
  getPawnAtTileId(int tileId) const; // Get the pawn at a specific tile
private:
  // Map pawn ID to the corresponding Pawn object
  std::unordered_map<int, std::shared_ptr<Pawn>> pawns;
};

#endif // PAWN_MANAGER_H
