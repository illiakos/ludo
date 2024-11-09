

#ifndef ROLL_DICE_HANDLER_H
#define ROLL_DICE_HANDLER_H

#include "EventHandler.h"
#include <memory>
class RollDiceHandler : public EventHandler {
public:
  void handleEvent(const std::shared_ptr<Event>& event) override;
};

#endif // !ROLL_DICE_HANDLER_H
