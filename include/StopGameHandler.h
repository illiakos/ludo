

#ifndef STOP_GAME_HANDLER_H
#define STOP_GAME_HANDLER_H

#include "Event.h"
#include "EventHandler.h"
#include <memory>
class StopGameHandler : public EventHandler {
public:
  void handleEvent(const std::shared_ptr<Event>& Event);
};

#endif // !STOP_GAME_HANDLER_H
