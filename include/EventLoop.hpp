#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <atomic>
#include <condition_variable>
#include <deque>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

class Event;
class EventDispatcher;

class EventLoop {
public:
  explicit EventLoop(EventDispatcher &dispatcher)
      : dispatcher(dispatcher), running(false), currentPlayerTurnEvent(nullptr) {}

  ~EventLoop() { stop(); }

  static void setInstance(EventLoop &instance);
  static EventLoop &getInstance();

  void enqueueEvent(const std::shared_ptr<Event> &event);
  void pushEvent(const std::shared_ptr<Event> &event);
  void start();
  void stop();
  void processEvents();
  void logEvents();

private:
  EventDispatcher &dispatcher;
  std::list<std::shared_ptr<Event>> events;

  std::mutex eventsMutex;
  std::condition_variable eventCondition;
  std::atomic<bool> running;
  std::thread eventThread;

  // Persistent state for handling immediate events and current turn
  std::deque<std::shared_ptr<Event>> immediateEvents;
  std::shared_ptr<Event> currentPlayerTurnEvent;

  static EventLoop *instance; // Singleton-like instance
};

#endif
