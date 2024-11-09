#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <list>
#include <memory>

class Event;
class EventDispatcher;

class EventLoop {
public:
    explicit EventLoop(EventDispatcher& dispatcher);
    void enqueueEvent(const std::shared_ptr<Event>& event);
    void pushEvent(const std::shared_ptr<Event>& event);
    void processEvents();

private:
    EventDispatcher& dispatcher;
    std::list<std::shared_ptr<Event>> events;
};

#endif
