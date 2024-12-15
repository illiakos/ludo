#ifndef WAIT_FOR_CHOOSE_PAWN_EVENT_H
#define WAIT_FOR_CHOOSE_PAWN_EVENT_H

#include "Event.hpp"

class WaitForChoosePawnEvent : public Event {
public:
    explicit WaitForChoosePawnEvent(int playerId, int diceRollResult)
        : playerId(playerId), diceRollResult(diceRollResult) {}

    int playerId;
    int diceRollResult;

    std::string getType() const {return "WaitForChoosePawnEvent";}

    void execute() {};
};

#endif // WAIT_FOR_CHOOSE_PAWN_EVENT_H
