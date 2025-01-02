#include "EventLoop.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>

EventLoop::EventLoop(EventDispatcher &dispatcher)
    : dispatcher(dispatcher), running(false) {}

EventLoop::~EventLoop() {
  stop(); // Ensure the thread is stopped before destruction
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

      event = events.front();
      events.pop_front();
    }

    // Process the event
    std::cout << "Processing event: " << event->getType() << std::endl;
    dispatcher.dispatch(event);

    if (event->getType() == "StopGameEvent") {
      std::cout << "Stopping the event loop.\n";
      break; // Exit the loop when StopGameEvent is encountered
    }

    if (event->isBlocking) {
      while (!event->isCompleted()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Waiting for completion...\n";
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
