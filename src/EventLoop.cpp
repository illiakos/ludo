#include "EventLoop.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "TurnManager.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>

/*EventLoop& EventLoop::getInstance() {*/
/*  static EventLoop instance;*/
/*  return instance;*/
/*}*/

EventLoop *EventLoop::instance = nullptr;

void EventLoop::setInstance(EventLoop &newInstance) {
  if (instance) {
    throw std::runtime_error("EventLoop instance is already set.");
  }
  instance = &newInstance;
}

EventLoop &EventLoop::getInstance() {
  if (!instance) {
    throw std::runtime_error("EventLoop instance has not been initialized.");
  }
  return *instance;
}

void EventLoop::enqueueEvent(const std::shared_ptr<Event> &event) {
  {
    std::lock_guard<std::mutex> lock(eventsMutex);
    events.push_back(event);
  }
  eventCondition.notify_one(); // Notify the event loop
}

void EventLoop::pushEvent(const std::shared_ptr<Event> &event) {
  {
    std::lock_guard<std::mutex> lock(eventsMutex);
    events.push_front(event);
  }
  eventCondition.notify_one(); // Notify the event loop
}

void EventLoop::logEvents() {

}

void EventLoop::processEvents() {
    while (running) {
        std::shared_ptr<Event> event;

        {
            std::unique_lock<std::mutex> lock(eventsMutex);

            // Wait for events or stop signal
            eventCondition.wait(lock, [this] { return !events.empty() || !running; });

            if (!running && events.empty()) {
                break; // Exit the loop if not running and no events to process
            }

            // Fetch the next event
            event = events.front();

            // If it's a PlayerTurnEvent and not completed, wait
            if (event == currentPlayerTurnEvent && !event->isCompleted()) {
                continue;
            }

            events.pop_front();
        }

        // Process immediate events directly
        if (event->isImmediate) {
            std::cout << "Processing immediate event: " << event->getType() << std::endl;
            dispatcher.dispatch(event);
            continue;
        }

        // Process non-immediate events
        std::cout << "Processing event: " << event->getType() << std::endl;
        dispatcher.dispatch(event);

        if (event->getType() == "StopGameEvent") {
            std::cout << "Stopping the event loop.\n";
            break;
        }

        if (event->isBlocking) {
            while (!event->isCompleted()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
}
void EventLoop::start() {
  if (running) {
    return; // Already running
  }

  running = true;
  eventThread = std::thread([this] { processEvents(); });
}

void EventLoop::stop() {
  {
    std::lock_guard<std::mutex> lock(eventsMutex);
    running = false;
  }
  eventCondition.notify_all(); // Wake up the loop if waiting
  if (eventThread.joinable()) {
    eventThread.join(); // Wait for the thread to finish
  }
}
