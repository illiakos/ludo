#ifndef MOVE_PAWN_HANDLER_H
#define MOVE_PAWN_HANDLER_H

#include "Board.hpp"
#include "EventHandler.hpp"
#include "MovePawnEvent.hpp"
#include "PawnManager.hpp"
#include <memory>

class MovePawnHandler : public EventHandler {
public:
  MovePawnHandler (Board &board, PawnManager &pawnManager)
      : board (board), pawnManager (pawnManager), EventHandler ("MovePawnHandler") {};

  void handleEvent (const std::shared_ptr<Event> &event) override;

protected:
  void returnPawnToBase (int pawnId);

private:
  Board &board;
  PawnManager &pawnManager;

  void moveRegularTiles(std::shared_ptr<Pawn> pawn, int steps);
  void handleSafeTile (Pawn &pawn);
  void handlePrefinishingTile (Pawn &pawn, int steps);
  void handleFinishingTile (Pawn &pawn);

  bool canMoveToFinishingTile (int currentPreFinishPosition, int steps);
};

#endif // MOVE_PAWN_HANDLER_H
