

#ifndef STOP_GAME_HANDLER_H
#define STOP_GAME_HANDLER_H

#include "Event.hpp"
#include "EventHandler.hpp"
#include <memory>
class StopGameHandler : public EventHandler {
public:
  void handleEvent(const std::shared_ptr<Event>& Event);

  StopGameHandler() : EventHandler("StopGame") {}

};

#endif // !STOP_GAME_HANDLER_H
