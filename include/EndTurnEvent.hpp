#ifndef END_TURN_EVENT_H
#define END_TURN_EVENT_H

#include "Event.hpp"
class EndTurnEvent : public Event {

public:
  explicit EndTurnEvent() {};
  std::string getType() const override {return "EndTurnEvent";}
  bool isCompleted() const override {return true;}

};

#endif // !END_TURN_EVENT_H
