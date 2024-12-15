

#ifndef STOP_GAME_EVENT_H
#define STOP_GAME_EVENT_H

#include "Event.hpp"
#include <string>
class StopGameEvent : public Event {
public:
    StopGameEvent() { isBlocking = true; }
    std::string getType() const override { return "StopGameEvent"; }

    bool isCompleted() const override { return true; }
};
#endif // !STOP_GAME_EVENT_H
