
#ifndef MOVE_PAWN_EVENT_H
#define MOVE_PAWN_EVENT_H

#include "Event.h"
class MovePawnEvent : public Event {
public:
  int playerId;
  int pawnId;
  int stepsCount;

  explicit MovePawnEvent(int playerId, int pawnId, int stepsCount)
      : playerId(playerId), pawnId(pawnId), stepsCount(stepsCount) {}
  std::string getType() const override { return "MovePawnEvent"; }
};

#endif // !MOVE_PAWN_EVENT_H
