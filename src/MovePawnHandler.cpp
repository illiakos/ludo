#include "MovePawnHandler.hpp"
#include "Base.hpp"
#include "BaseManager.hpp"
#include "MovePawnEvent.hpp"
#include "PawnManager.hpp"
#include "SpecialTiles.hpp"
#include "TileContext.hpp"
#include "TileManager.hpp"
#include <iostream>
#include <memory>

/*MovePawnHandler::MovePawnHandler(Board& board, PawnManager& pawnManager)*/
/*    : EventHandler("MovePawnHandler"), board(board), pawnManager(pawnManager) {}*/

void MovePawnHandler::handleEvent (const std::shared_ptr<Event> &event) {
  auto moveEvent = std::dynamic_pointer_cast<MovePawnEvent> (event);
  if (moveEvent) {
    TileManager &tileManager = TileManager::getInstance ();
    auto &drawer = MapDrawer::getInstance ();
    auto pawn = pawnManager.getPawn (moveEvent->getPawnId ());
    int steps = moveEvent->stepsCount;

    drawer.removeRenderable (pawn);
    switch (pawn->getContext ()) {
    case TileContext::Base:

      if (steps == 6) {
        auto &bm = BaseManager::getInstance ();
        auto base = bm.getBaseByTeamId (pawn->getTeamId ());
        if (!base) {
          std::cerr << "Error: Base not found for team ID " << pawn->getTeamId () << "\n";
          return;
        }

        int startingTileId = base->getStartingTileId ();
        auto startingTile = tileManager.findTileByContextAndPosition (
            TileContext::Walkable, startingTileId);
        if (!startingTile) {
          std::cerr << "Error: Starting tile not found for tile ID " << startingTileId << "\n";
          return;
        }

        pawn->setTileId (startingTileId);
        pawn->setContext (TileContext::Walkable);
        auto tileDimensions = startingTile->getDimensions ();
        auto newDimensions = Dimensions (tileDimensions.x,
            tileDimensions.y,
            pawn->getDimensions ().dx,
            pawn->getDimensions ().dy);
        pawn->setDimensions (newDimensions);
        std::cout << "Pawn " << pawn->getId () << " moved from Base to Walkable starting tile.\n";

        /*base->freeSlot();*/
      } else {
        std::cout << "Pawn " << pawn->getId () << " cannot leave base without rolling a 6.\n";
      }
      return;
      break;
    case TileContext::Walkable:

      moveRegularTiles (*pawn, steps);
    default:

      break;
    }
    // Case 1: Pawn is in Base

    // Case 3: Pawn is in Walkable context and might move to Finishing context
    /*if (pawn->getContext() == TileContext::Walkable) {*/
    /*    int currentTilePosition = pawn->getTileId();*/
    /*    int targetTilePosition = currentTilePosition + steps;*/
    /**/
    /*    if (targetTilePosition > 50) { // Example threshold for finishing context*/
    /*        int finishingTilePosition = targetTilePosition - 50;*/
    /**/
    /*        auto tile = tileManager.findTileByContextAndPosition(TileContext::Finishing,
     * finishingTilePosition);*/
    /*        PrefinishingTile* finishingTile = dynamic_cast<PrefinishingTile*>(tile.get());*/
    /*        if (finishingTile && finishingTile->getTeamId() == pawn->getPlayerId()) {*/
    /*            pawn->setTileId(finishingTilePosition);*/
    /*            pawn->setContext(TileContext::Finishing);*/
    /*            pawn->setDimensions(finishingTile->getDimensions());*/
    /*            std::cout << "Pawn " << pawn->getId() << " moved to finishing tiles.\n";*/
    /*            drawer.addRenderable(pawn);*/
    /*            return;*/
    /*        } else {*/
    /*            std::cout << "Pawn " << pawn->getId() << " cannot enter the finishing tiles of
     * another team.\n";*/
    /*            return;*/
    /*        }*/
    /*    }*/
    /**/
    /*    drawer.addRenderable(pawn);*/
    /*    return;*/
    /*}*/

    // Case 2: Regular movement
    moveRegularTiles (*pawn, steps);
    drawer.addRenderable (pawn);
  }
}

void MovePawnHandler::moveRegularTiles (Pawn &pawn, int steps) {
  auto &drawer = MapDrawer::getInstance ();
  int currentTileId = pawn.getTileId ();
  auto currentTile = TileManager::getInstance ().findTileById (currentTileId);
  int currentPosition = currentTile->getPosition ();
  drawer.removeRenderable (std::make_shared<Pawn> (pawn));
  for (int i = 0; i < steps; i++) {
    currentPosition++;

    Tile *tile = board.getTileByPosition (currentTileId);

    if (!tile) {
      std::cerr << "Error: Tile not found at position " << currentTileId << "\n";
      return;
    }

    // Check if the tile is a TransitionTile
    auto transitionTile = dynamic_cast<TransitionTile *> (tile);
    if (transitionTile && transitionTile->getTeamId () == pawn.getPlayerId ()) {
      // Move to the starting finishing tile
      int finishingTileStartPosition = transitionTile->getFinishingTileStartPosition ();
      auto finishingTile = TileManager::getInstance ().findTileByContextAndPosition (
          TileContext::Finishing, finishingTileStartPosition);

      if (finishingTile) {
        pawn.setTileId (finishingTileStartPosition);
        pawn.setContext (TileContext::Finishing);
        pawn.setDimensions (finishingTile->getDimensions ());
        std::cout << "Pawn " << pawn.getId () << " moved to Finishing context.\n";
        return;
      } else {
        std::cerr << "Error: Finishing tile not found at position " << finishingTileStartPosition
                  << "\n";
        return;
      }
    }

    // Regular movement
    pawn.setTileId (currentTileId);

    // Check for eating pawns, safe tiles, etc. (existing logic)
  }
}

void MovePawnHandler::returnPawnToBase (int pawnId) {
}

void MovePawnHandler::handleSafeTile (Pawn &pawn) {
  std::cout << "Pawn " << pawn.getId () << " is safe on tile " << pawn.getTileId () << "\n";
  // Additional safe tile behavior can be added here
}

void MovePawnHandler::handlePrefinishingTile (Pawn &pawn, int steps) {
  int currentPreFinishPosition = pawn.getTileId ();
  int firstFinishingTilePosition =
      board.getTileByPosition (currentPreFinishPosition)->getPosition ();

  if (canMoveToFinishingTile (currentPreFinishPosition, steps)) {
    int newPosition = currentPreFinishPosition + steps;
    if (newPosition == firstFinishingTilePosition + 5) {
      std::cout << "Pawn " << pawn.getId () << " reached the finishing tile!\n";
    }
    pawn.setTileId (newPosition);
  } else {
    std::cout << "Pawn " << pawn.getId () << " cannot move due to insufficient steps.\n";
  }
}

void MovePawnHandler::handleFinishingTile (Pawn &pawn) {
  std::cout << "Pawn " << pawn.getId () << " has finished!\n";
  // Mark pawn as finished and update the game state
}

bool MovePawnHandler::canMoveToFinishingTile (int currentPreFinishPosition, int steps) {
  return (currentPreFinishPosition + steps <= currentPreFinishPosition + 5);
}
