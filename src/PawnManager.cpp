#include "PawnManager.h"
#include <iostream>

void PawnManager::addPawn(int playerId, int pawnId, int startingTileId) {
    if (pawns[playerId].find(pawnId) == pawns[playerId].end()) {
        auto pawn = std::make_shared<Pawn>();
        pawn->id = pawnId;
        pawn->playerId = playerId;
        pawn->tileId = startingTileId;
        pawns[playerId][pawnId] = pawn;
        std::cout << "Added Pawn " << pawnId << " for Player " << playerId
                  << " at tile ID " << startingTileId << ".\n";
    }
}

void PawnManager::movePawn(int playerId, int pawnId, int newTileId) {
    auto pawn = getPawn(playerId, pawnId);
    if (pawn) {
        pawn->tileId = newTileId;
        std::cout << "Moved Pawn " << pawnId << " for Player " << playerId
                  << " to tile ID " << newTileId << ".\n";
    } else {
        std::cerr << "Pawn " << pawnId << " for Player " << playerId << " not found!\n";
    }
}

const std::shared_ptr<Pawn> PawnManager::getPawn(int playerId, int pawnId) const {
    auto playerIt = pawns.find(playerId);
    if (playerIt != pawns.end()) {
        auto pawnIt = playerIt->second.find(pawnId);
        if (pawnIt != playerIt->second.end()) {
            return pawnIt->second;
        }
    }
    return nullptr;
}

int PawnManager::getPawnTileId(int playerId, int pawnId) const {
    auto pawn = getPawn(playerId, pawnId);
    return pawn ? pawn->tileId : -1; // Return -1 if the pawn is not found
}
