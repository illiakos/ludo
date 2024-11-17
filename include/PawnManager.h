#ifndef PAWN_MANAGER_H
#define PAWN_MANAGER_H

#include <unordered_map>
#include <memory>
#include "Pawn.h"

class PawnManager {
public:
    void addPawn(int playerId, int pawnId, int startingTileId);
    void movePawn(int playerId, int pawnId, int newTileId);

    const std::shared_ptr<Pawn> getPawn(int playerId, int pawnId) const;
    int getPawnTileId(int playerId, int pawnId) const;

private:
    // Map player ID to their pawns, and each pawn ID to the corresponding Pawn object
    std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Pawn>>> pawns;
};

#endif // PAWN_MANAGER_H
