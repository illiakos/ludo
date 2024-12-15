#include "StopGameHandler.h"
#include "StopGameEvent.hpp"
#include <iostream>
#include <memory>

void StopGameHandler::handleEvent(
    const std::shared_ptr<Event> &event){
  auto stopEvent = std::dynamic_pointer_cast<StopGameEvent>(event);

  if (stopEvent) {
    std::cout << "Stop game event received. Ending game loop.\n";
  }
}
