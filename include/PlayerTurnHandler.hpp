

#ifndef PLAYER_TURN_HANDLER_H
#define PLAYER_TURN_HANDLER_H

#include "EventHandler.hpp"
#include "EventLoop.hpp"
#include "TurnManager.hpp"

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
