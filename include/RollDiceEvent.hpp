

#ifndef ROLL_DICE_EVENT_H
#define ROLL_DICE_EVENT_H

#include "Event.hpp"
class RollDiceEvent : public Event {
public:
  int playerId;

  explicit RollDiceEvent(int playerId) : Event(true), playerId(playerId) {}
  std::string getType() const {return "RollDiceEvent";}

  void execute() {};

};

#endif // !ROLL_DICE_EVENT_H
