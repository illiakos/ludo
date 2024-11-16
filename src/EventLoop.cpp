#include "EventLoop.h"
#include "Event.h"
#include "EventDispatcher.h"
#include <iostream>
#include <memory>
#include <ostream>

EventLoop::EventLoop(EventDispatcher &dispatcher) : dispatcher(dispatcher) {}

void EventLoop::enqueueEvent(const std::shared_ptr<Event> &event) {
  events.push_back(event);
}

void EventLoop::pushEvent(const std::shared_ptr<Event> &event) {
  events.push_front(event);
}

void EventLoop::processEvents() {
    while (!events.empty()) {
        auto event = events.front();
        events.pop_front();
        std::cout << event->getType() << std::endl;
        dispatcher.dispatch(event);

        if (event->getType() == "StopGameEvent") {
            std::cout << "Stopping the event loop.\n";
            break; // Exit the loop when StopGameEvent is encountered
        }

        if (event->isBlocking) {
            while (!event->isCompleted()) {
                // Wait for completion, add sleep or other waiting logic if needed
              std::cout << "waiting for completion" << std::endl;
            }
        }
    }
}
