
#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class Event;
class EventHandler;

class EventDispatcher {
public:
  void subscribe(const std::string &eventType,
                 const std::shared_ptr<EventHandler> &handler);
  void unsubscribe(const std::string &eventType,
                   const std::string &handlerName);
  void dispatch(const std::shared_ptr<Event> &event);

private:
  std::map<std::string, std::vector<std::shared_ptr<EventHandler>>> handlers;
};
#endif // ! EVENT_DISPATCHER_H
