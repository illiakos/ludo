

#ifndef ROLL_DICE_HANDLER_H
#define ROLL_DICE_HANDLER_H

#include "EventHandler.h"
#include "EventLoop.h"
#include <memory>

class TurnManager;

class RollDiceHandler : public EventHandler {
public:
  void handleEvent(const std::shared_ptr<Event>& event) override;

  RollDiceHandler(TurnManager& turnManager, EventLoop& eventLoop) : EventHandler("RollDice"), turnManager(turnManager), eventLoop(eventLoop) {};
private:
  TurnManager& turnManager;
  EventLoop& eventLoop;
};

#endif // !ROLL_DICE_HANDLER_H
