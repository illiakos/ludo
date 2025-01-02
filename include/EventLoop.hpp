#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <atomic>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

class Event;
class EventDispatcher;

class EventLoop {
public:
  explicit EventLoop(EventDispatcher &dispatcher);
  ~EventLoop();
  void enqueueEvent(const std::shared_ptr<Event> &event);
  void pushEvent(const std::shared_ptr<Event> &event);
  void processEvents();

  void start();
  void stop();

private:
  EventDispatcher &dispatcher;
  std::list<std::shared_ptr<Event>> events;

  std::mutex eventsMutex;
  std::condition_variable eventCondition;
  std::atomic<bool> running;
  std::thread eventThread;
};

#endif
