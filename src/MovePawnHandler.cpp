#include "MovePawnHandler.hpp"
#include "MovePawnEvent.hpp"
#include "PawnManager.hpp"
#include "SpecialTiles.hpp"
#include <iostream>
#include <memory>

/*MovePawnHandler::MovePawnHandler(Board& board, PawnManager& pawnManager)*/
/*    : EventHandler("MovePawnHandler"), board(board), pawnManager(pawnManager) {}*/

void MovePawnHandler::handleEvent(const std::shared_ptr<Event>& event) {
    auto moveEvent = std::dynamic_pointer_cast<MovePawnEvent>(event);
    if (moveEvent) {
        auto pawn = pawnManager.getPawn(moveEvent->getPawnId());
        int steps = moveEvent->stepsCount;

        
        // Check if pawn is already on prefinishing tiles
        const Tile* currentTile = board.getTileByPosition(pawn->getTileId());
        auto preFinishTile = dynamic_cast<const PrefinishingTile*>(currentTile);
        if (preFinishTile) {
            handlePrefinishingTile(*pawn, steps);
            return;
        }

        // Handle regular movement
        moveRegularTiles(*pawn, steps);

        // Check the type of the new tile and handle it
        const Tile* newTile = board.getTileByPosition(pawn->getTileId());
        if (dynamic_cast<const SafeTile*>(newTile) || dynamic_cast<const StartingTile*>(newTile)) {
            handleSafeTile(*pawn);
        } else if (dynamic_cast<const PrefinishingTile*>(newTile)) {
            handlePrefinishingTile(*pawn, steps);
        } else if (dynamic_cast<const FinishingTile*>(newTile)) {
            handleFinishingTile(*pawn);
        }
    }
}

void MovePawnHandler::moveRegularTiles(Pawn& pawn, int steps) {
    int currentTileId = pawn.getTileId();

    for (int i = 0; i < steps; i++) {
        currentTileId++;
        const Tile* tile = board.getTileByPosition(currentTileId);

        if (tile == nullptr) {
            std::cerr << "Error: Tile not found at position " << currentTileId << "\n";
            return;
        }

        // Check if pawn moves to prefinishing tile
        if (auto preFinishTile = dynamic_cast<const PrefinishingTile*>(tile)) {
            if (preFinishTile->getTeamId() == pawn.getPlayerId()) {
                pawn.setTileId(preFinishTile->getFirstFinishingTilePosition());
                return;
            }
        }

        // Check for eating pawns
        if (pawnManager.hasPawnAtTile(currentTileId)) {
            auto otherPawn = pawnManager.getPawnAtTileId(currentTileId);
            if (otherPawn->getPlayerId() != pawn.getPlayerId()) {
                std::cout << "Pawn " << pawn.getId() << " eats Pawn " << otherPawn->getId() << "\n";
                returnPawnToBase(otherPawn->getTileId());
            }
        }
    }

    pawn.setTileId(currentTileId);
}


void MovePawnHandler::returnPawnToBase(int pawnId) {
  
}

void MovePawnHandler::handleSafeTile(Pawn& pawn) {
    std::cout << "Pawn " << pawn.getId() << " is safe on tile " << pawn.getTileId() << "\n";
    // Additional safe tile behavior can be added here
}

void MovePawnHandler::handlePrefinishingTile(Pawn& pawn, int steps) {
    int currentPreFinishPosition = pawn.getTileId();
    int firstFinishingTilePosition = board.getTileByPosition(currentPreFinishPosition)->getPosition();

    if (canMoveToFinishingTile(currentPreFinishPosition, steps)) {
        int newPosition = currentPreFinishPosition + steps;
        if (newPosition == firstFinishingTilePosition + 5) {
            std::cout << "Pawn " << pawn.getId() << " reached the finishing tile!\n";
        }
        pawn.setTileId(newPosition);
    } else {
        std::cout << "Pawn " << pawn.getId() << " cannot move due to insufficient steps.\n";
    }
}

void MovePawnHandler::handleFinishingTile(Pawn& pawn) {
    std::cout << "Pawn " << pawn.getId() << " has finished!\n";
    // Mark pawn as finished and update the game state
}

bool MovePawnHandler::canMoveToFinishingTile(int currentPreFinishPosition, int steps) {
    return (currentPreFinishPosition + steps <= currentPreFinishPosition + 5);
}
