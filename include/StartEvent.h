

#ifndef START_TURN_EVENT_H
#define START_TURN_EVENT_H

#include "Event.h"

class StartTurnEvent : public Event {
public:
  StartTurnEvent(int playerId) : playerId(playerId) {};
  void execute(Game& game) override;

private:
  int playerId;

};

#endif // !START_TURN_EVENT_H
