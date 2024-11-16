#ifndef WAIT_FOR_CHOOSE_PAWN_HANDLER_H
#define WAIT_FOR_CHOOSE_PAWN_HANDLER_H

#include "EventHandler.h"
#include "TurnManager.h"
#include "EventLoop.h"

class WaitForChoosePawnHandler : public EventHandler {
public:
    WaitForChoosePawnHandler(TurnManager& turnManager, EventLoop& eventLoop)
        : EventHandler("WaitForChoosePawnHandler"), turnManager(turnManager), eventLoop(eventLoop) {}

    void handleEvent(const std::shared_ptr<Event>& event) override;

private:
    TurnManager& turnManager;
    EventLoop& eventLoop;
};

#endif // WAIT_FOR_CHOOSE_PAWN_HANDLER_H
