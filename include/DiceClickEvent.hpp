#ifndef DICE_CLICK_EVENT_HPP
#define DICE_CLICK_EVENT_HPP


#include "Event.hpp"
#include <string>
class DiceClickEvent : public Event {

public:
  DiceClickEvent() { isBlocking = false; isImmediate = true;}
  std::string getType() const override { return "DiceClickEvent"; }

  bool isCompleted() const override {return true;}

};



#endif // !DICE_CLICK_EVENT_HPP
