

#ifndef ROLL_DICE_EVENT_H
#define ROLL_DICE_EVENT_H



#include "Event.h"
class RollDiceEvent : public Event {
public:
  RollDiceEvent(int playerId) : playerId(playerId) {}
  void execute(Game& game) override;

private: 
  int playerId;
};

#endif // !ROLL_DICE_EVENT_H
