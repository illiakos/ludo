#include "PawnManager.hpp"
#include "Coordinates.hpp"
#include <iostream>

void PawnManager::addPawn(int pawnId, int startingTileId) {
    if (pawns.find(pawnId) == pawns.end()) {
        // TODO: create some mechanism to get coordinates by tile id
        auto coords = Coordinates(0,0,0); 
        auto pawn = std::make_shared<Pawn>(pawnId, startingTileId, coords);
        pawns[pawnId] = pawn;
        std::cout << "Added Pawn " << pawnId << " at tile ID " << startingTileId << ".\n";
    } else {
        std::cerr << "Pawn " << pawnId << " already exists!\n";
    }
}

void PawnManager::movePawn(int pawnId, int newTileId) {
    auto pawn = getPawn(pawnId);
    if (pawn) {
        pawn->setTileId(newTileId);
        std::cout << "Moved Pawn " << pawnId << " to tile ID " << newTileId << ".\n";
    } else {
        std::cerr << "Pawn " << pawnId << " not found!\n";
    }
}

std::shared_ptr<Pawn> PawnManager::getPawn(int pawnId) const {
    auto pawnIt = pawns.find(pawnId);
    if (pawnIt != pawns.end()) {
        return pawnIt->second;
    }
    return nullptr;
}

int PawnManager::getPawnTileId(int pawnId) const {
    auto pawn = getPawn(pawnId);
    return pawn ? pawn->getTileId() : -1; // Return -1 if the pawn is not found
}

std::shared_ptr<Pawn> PawnManager::getPawnAtTileId(int tileId) const {
    for (const auto& [pawnId, pawn] : pawns) {
        if (pawn->getTileId() == tileId) {
            return pawn;
        }
    }
    return nullptr; // Return nullptr if no pawn exists at the specified tile
}

bool PawnManager::hasPawnAtTile(int tileId) const {
    for (const auto& [pawnId, pawn] : pawns) {
        if (pawn->getTileId() == tileId) {
            return true;
        }
    }
    return false;
}
