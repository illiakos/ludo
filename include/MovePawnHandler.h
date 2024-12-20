#ifndef MOVE_PAWN_HANDLER_H
#define MOVE_PAWN_HANDLER_H

#include "EventHandler.h"
#include "Board.h"
#include "PawnManager.h"
#include "MovePawnEvent.h"
#include <memory>

class MovePawnHandler : public EventHandler {
public:
    MovePawnHandler(Board& board, PawnManager& pawnManager);

    void handleEvent(const std::shared_ptr<Event>& event) override;

private:
    Board& board;
    PawnManager& pawnManager;

    void moveRegularTiles(Pawn& pawn, int steps);
    void handleSafeTile(Pawn& pawn);
    void handlePrefinishingTile(Pawn& pawn, int steps);
    void handleFinishingTile(Pawn& pawn);

    bool canMoveToFinishingTile(int currentPreFinishPosition, int steps);
};

#endif // MOVE_PAWN_HANDLER_H
