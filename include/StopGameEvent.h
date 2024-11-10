

#ifndef STOP_GAME_EVENT_H
#define STOP_GAME_EVENT_H

#include "Event.h"
#include <string>
class StopGameEvent : public Event {
public:
    StopGameEvent() { isBlocking = true; }
    std::string getType() const override { return "StopGameEvent"; }

    bool isCompleted() const override { return true; }
    void execute() override {};
};
#endif // !STOP_GAME_EVENT_H
