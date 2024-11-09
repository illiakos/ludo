
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Event.h"
#include <memory>
#include <string>

class EventHandler {

protected:
  std::string handlerName;
public:
  explicit EventHandler(std::string name) : handlerName(name) {} 
  virtual ~EventHandler() = default;
  virtual void handleEvent(const std::shared_ptr<Event>& event) = 0;
  std::string getName() const {
    return handlerName;
  } 
};


#endif // !EVENT_HANDLER_H
