

#ifndef PLAYER_TURN_HANDLER_H
#define PLAYER_TURN_HANDLER_H

#include "EventHandler.h"
#include "EventLoop.h"
#include "TurnManager.h"

/*class EventLoop;*/

class PlayerTurnHandler : public EventHandler {
public:
    PlayerTurnHandler(EventLoop& loop, int totalPlayers, TurnManager& turnManager);

    void handleEvent(const std::shared_ptr<Event>& event) override;

private:
    EventLoop& eventLoop;
    int totalPlayers;
    TurnManager& turnManager;
};

#endif // !PLAYER_TURN_EVENT_H
