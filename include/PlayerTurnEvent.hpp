

#ifndef PLAYER_TURN_EVENT_H
#define PLAYER_TURN_EVENT_H

#include "Event.hpp"
#include <iostream>
class PlayerTurnEvent : public Event {
public:
  explicit PlayerTurnEvent(int playerId)
      : playerId(playerId), Event(true), turnCompleted(false) {}

  std::string getType() const override { return "PlayerTurnEvent"; }

  bool isCompleted() const override { return turnCompleted; }

  void completeTurn() { 
    std::cout << "Turn completed" << std::endl;
    turnCompleted = true; 
  }

  int playerId;

private:
  bool turnCompleted;
};

#endif // !PLAYER_TURN_EVENT_H
