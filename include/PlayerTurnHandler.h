

#ifndef PLAYER_TURN_HANDLER_H
#define PLAYER_TURN_HANDLER_H

#include "EventHandler.h"
#include "EventLoop.h"
/*class EventLoop;*/

class PlayerTurnHandler : public EventHandler {
public:
    PlayerTurnHandler(EventLoop& loop, int totalPlayers);

    void handleEvent(const std::shared_ptr<Event>& event) override;

private:
    EventLoop& eventLoop;
    int totalPlayers;
};

#endif // !PLAYER_TURN_EVENT_H
