

#ifndef MOVE_PAWN_HANDLER_H
#define MOVE_PAWN_HANDLER_H

#include "EventHandler.h"
#include <memory>
class MovePawnHandler : public EventHandler {
public:
  void handleEvent(const std::shared_ptr<Event>& event);
};

#endif // !
