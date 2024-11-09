#include "EventDispatcher.h"
#include "Event.h"
#include "EventHandler.h"

void EventDispatcher::subscribe(const std::string& eventType, const std::shared_ptr<EventHandler>& handler) {
    handlers[eventType].push_back(handler);
}

void EventDispatcher::unsubscribe(const std::string& eventType, const std::string& handlerName) {
    auto it = handlers.find(eventType);
    if (it != handlers.end()) {
        auto& handlerList = it->second;
        handlerList.erase(std::remove_if(handlerList.begin(), handlerList.end(),
                                         [&handlerName](const std::shared_ptr<EventHandler>& handler) {
                                             return handler->getHandlerName() == handlerName;
                                         }),
                          handlerList.end());
    }
}

void EventDispatcher::dispatch(const std::shared_ptr<Event>& event) {
    auto it = handlers.find(event->getType());
    if (it != handlers.end()) {
        for (auto& handler : it->second) {
            handler->handleEvent(event);
        }
    }
}
