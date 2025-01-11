#include "MovePawnHandler.hpp"

#include <iostream>
#include <memory>
#include <ostream>

#include "Base.hpp"
#include "BaseManager.hpp"
#include "EndTurnEvent.hpp"
#include "EventLoop.hpp"
#include "MovePawnEvent.hpp"
#include "PawnManager.hpp"
#include "SpecialTiles.hpp"
#include "TeamManager.hpp"
#include "TileContext.hpp"
#include "TileManager.hpp"

void MovePawnHandler::handleEvent(const std::shared_ptr<Event> &event) {
  std::cout << "handling event" << endl;
  auto moveEvent = std::dynamic_pointer_cast<MovePawnEvent>(event);
  if (moveEvent) {
    TileManager &tileManager = TileManager::getInstance();
    auto &drawer = MapDrawer::getInstance();
    auto pawn = pawnManager.getPawn(moveEvent->getPawnId());
    int steps = moveEvent->stepsCount;
    std::cout << "HANDLE EVENT" << std::endl;
    drawer.removeRenderable(pawn);
    switch (pawn->getContext()) {
    case TileContext::Finishing:
      moveAtFinishing(pawn, steps);
      break;
    case TileContext::Base:

      if (steps == 6) {
        auto &bm = BaseManager::getInstance();
        std::cout << pawn->getTeamId() << std::endl;
        auto base = bm.getBaseByTeamId(pawn->getTeamId());
        std::cout << base->toString() << std::endl;
        if (!base) {
          std::cerr << "Error: Base not found for team ID " << pawn->getTeamId()
                    << " \n";
          return;
        }

        int startingTileId = base->getStartingTileId();

        tileManager.printTiles();

        auto startingTile = tileManager.findTileByContextAndPosition(
            TileContext::Walkable, startingTileId);

        std::cout << startingTile->toString() << endl;

        if (!startingTile) {
          std::cerr << "Error: Starting tile not found for tile ID "
                    << startingTileId << "\n";
          return;
        }
        std::cout << "Setting tile id to starting : " << startingTileId << endl;
        pawn->setTileId(startingTileId);
        pawn->setActive(true);
        pawn->setContext(TileContext::Walkable);
        auto tileDimensions = startingTile->getDimensions();
        auto newDimensions =
            Dimensions(tileDimensions.x, tileDimensions.y,
                       pawn->getDimensions().dx, pawn->getDimensions().dy);
        pawn->setDimensions(newDimensions);
        pawn->setActive(true);
        std::cout << "Pawn " << pawn->getId()
                  << " moved from Base to Walkable starting tile.\n";
      } else {
        std::cout << "Pawn " << pawn->getId()
                  << " cannot leave base without rolling a 6.\n";
      }
      drawer.addRenderable(pawn);
      return;
      break;
    case TileContext::Walkable:

      moveRegularTiles(pawn, steps);
    default:

      break;
    }
  }
  auto eventLoop = EventLoop::getInstance();
  eventLoop->enqueueEvent(std::make_shared<EndTurnEvent>());
}

void MovePawnHandler::moveAtFinishing(std::shared_ptr<Pawn> pawn, int steps) {
  auto &tm = TileManager::getInstance();
  auto &drawer = MapDrawer::getInstance();
  int currentTileId = pawn->getTileId();
  cout << currentTileId << "KURDE" << endl;
  auto currentTile = tm.findTileById(currentTileId);
  drawer.removeRenderable(pawn);

  int nextPos = currentTile->getPosition() + steps;
  cout << currentTile->getPosition() << steps << "ABNOGBCVBVBVBVBBVVBVB"
       << endl;
  if (nextPos > 6) {
    // If the pawn moves beyond the finishing tiles, it can't move further.
    drawer.addRenderable(pawn);
    return;
  } else if (nextPos == 6) {
    // Retrieve the prelast and last tiles
    auto prelastFinishingTile = tm.findPrefinishingTileByContextPositionAndTeam(
        TileContext::Finishing, 4, pawn->getTeamId());
    auto lastFinishingTile = tm.findPrefinishingTileByContextPositionAndTeam(
        TileContext::Finishing, 5, pawn->getTeamId());

    if (prelastFinishingTile && lastFinishingTile) {
      // Determine the direction of the arrow based on the relative positions of
      // the last and prelast tiles
      int dx = lastFinishingTile->getDimensions().x -
               prelastFinishingTile->getDimensions().x;
      int dy = lastFinishingTile->getDimensions().y -
               prelastFinishingTile->getDimensions().y;

      // Move the pawn one step further in the direction of the arrow
      float finalX = lastFinishingTile->getDimensions().x + dx;
      float finalY = lastFinishingTile->getDimensions().y + dy;

      pawn->setTileId(-1);    // Mark pawn as finished
      pawn->setActive(false); // Mark pawn as inactive
      pawn->setDimensions(
          Dimensions(finalX, finalY, pawn->getDimensions().dx,
                     pawn->getDimensions().dy)); // Move pawn to the arrow tile
      pawn->setActive(false);
      auto& teamManager = TeamManager::getInstance();
      teamManager.addPointsToTeam(pawn->getTeamId(), 1);
      drawer.addRenderable(pawn); // Add the pawn back to the renderable list
      return;
    }
  } else {
    // Regular movement in the finishing tiles
    auto targetTile = tm.findPrefinishingTileByContextPositionAndTeam(
        TileContext::Finishing, nextPos, pawn->getTeamId());
    if (targetTile) {
      pawn->setTileId(targetTile->getId()); // Update pawn's tile ID
      pawn->setDimensions(
          targetTile
              ->getDimensions()); // Update dimensions to match the target tile
    }
  }
  std::cout << "new dims : " << pawn->getDimensions() << endl;
  drawer.addRenderable(pawn); // Add the pawn back to the renderable list
}
void MovePawnHandler::moveRegularTiles(std::shared_ptr<Pawn> pawn, int steps) {

  // TODO: Check beforehand whether final destination is the transition tile and
  // render pawn there

  std::cout << "moving on regular tiles, steps : " << steps << endl;
  auto &tm = TileManager::getInstance();
  auto &drawer = MapDrawer::getInstance();
  int currentTileId = pawn->getTileId();
  std::cout << "Tile id : " << pawn->getTileId() << endl;
  auto currentTile = tm.findTileById(pawn->getTileId());
  std::cout << "-----------------------------" << endl;
  std::cout << currentTile->toString() << endl;

  std::cout << "-----------------------------" << endl;
  int currentPosition = currentTile->getPosition();
  drawer.removeRenderable(pawn);
  for (int i = 0; i < steps; i++) {
    std::cout << "cycled once, position: " << currentPosition << endl;

    currentPosition++;
    if (currentPosition > 51) {
      currentPosition = 1;
    }
    auto tile =
        tm.findTileByContextAndPosition(TileContext::Walkable, currentPosition);

    if (!tile) {
      std::cerr << "Error: Tile not found at position " << currentPosition
                << "\n";
      return;
    }

    // Check if the tile is a TransitionTile
    auto transitionTile = dynamic_pointer_cast<TransitionTile>(tile);
    if (transitionTile && transitionTile->getTeamId() == pawn->getTeamId()) {

      // Move to the starting finishing tile
      int finishingTileStartPosition = transitionTile->getFinishingTileStartPosition();

      std::cout << "Steps: " << steps << std::endl;
      auto finishingTile =
          TileManager::getInstance()
              .findPrefinishingTileByContextPositionAndTeam(
                  TileContext::Finishing, steps - i - 1, pawn->getTeamId());

      if (finishingTile) {
        auto newFinishingTile =
            TileManager::getInstance()
                .findPrefinishingTileByContextPositionAndTeam(
                    TileContext::Finishing, 1, pawn->getTeamId());
        pawn->setTileId(finishingTile->getId());
        pawn->setContext(TileContext::Finishing);
        pawn->setDimensions(Dimensions(
            finishingTile->getDimensions().x, finishingTile->getDimensions().y,
            pawn->getDimensions().dx, pawn->getDimensions().dy));
        std::cout << "Pawn " << pawn->getDimensions()
                  << " moved to Finishing context.\n";
        drawer.addRenderable(pawn);
        return;
      } else {
        std::cerr << "Error: Finishing tile not found at position "
                  << finishingTileStartPosition << "\n";

        drawer.addRenderable(pawn);
        return;
      }
    }

    // Check for eating pawns, safe tiles, etc. (existing logic)
  }

  std::cout << steps << endl;
  std::cout << "Current position :" << currentPosition << endl;
  auto destinationTile =
      tm.findTileByContextAndPosition(TileContext::Walkable, currentPosition);
  std::cout << "New tile id: " << destinationTile->getId() << endl;
  // Regular movement
  //

  std::cout << "Pawn with id : " << pawn->getId()
            << " , has old tile id : " << pawn->getTileId() << endl;

  pawn->setTileId(destinationTile->getId());
  auto newDimensions = Dimensions(
      destinationTile->getDimensions().x, destinationTile->getDimensions().y,
      pawn->getDimensions().dx, pawn->getDimensions().dy);
  pawn->setDimensions(newDimensions);
  pawn->setContext(TileContext::Walkable);
  std::cout << "DTILE id  : " << destinationTile->getId() << endl;
  std::cout << "came here" << endl;
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

  std::cout << "Pawn with id : " << pawn->getId()
            << " , has new tile id : " << pawn->getTileId() << endl;

  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  drawer.addRenderable(pawn);
}

void MovePawnHandler::returnPawnToBase(int pawnId) {}

void MovePawnHandler::handleSafeTile(Pawn &pawn) {
  std::cout << "Pawn " << pawn.getId() << " is safe on tile "
            << pawn.getTileId() << "\n";
  // Additional safe tile behavior can be added here
}

void MovePawnHandler::handlePrefinishingTile(Pawn &pawn, int steps) {
  int currentPreFinishPosition = pawn.getTileId();
  int firstFinishingTilePosition =
      board.getTileByPosition(currentPreFinishPosition)->getPosition();
  cout << currentPreFinishPosition << "ASHSHSHSHS" << endl;
  if (canMoveToFinishingTile(currentPreFinishPosition, steps)) {
    int newPosition = currentPreFinishPosition + steps;
    if (newPosition == firstFinishingTilePosition + 5) {
      std::cout << "Pawn " << pawn.getId() << " reached the finishing tile!\n";
    }
    pawn.setTileId(newPosition);
  } else {
    std::cout << "Pawn " << pawn.getId()
              << " cannot move due to insufficient steps.\n";
  }
}

void MovePawnHandler::handleFinishingTile(Pawn &pawn) {
  std::cout << "Pawn " << pawn.getId() << " has finished!\n";
  // Mark pawn as finished and update the game state
}

bool MovePawnHandler::canMoveToFinishingTile(int currentPreFinishPosition,
                                             int steps) {
  return (currentPreFinishPosition + steps <= currentPreFinishPosition + 5);
}
