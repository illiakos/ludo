

#ifndef PLAYER_TURN_HANDLER_H
#define PLAYER_TURN_HANDLER_H

#include "Event.hpp"
#include "EventHandler.hpp"
#include "EventLoop.hpp"
#include "PlayerTurnEvent.hpp"
#include "TurnManager.hpp"
#include <memory>

/*class EventLoop;*/

class PlayerTurnHandler : public EventHandler {
public:
  PlayerTurnHandler(std::shared_ptr<EventLoop> loop, int totalPlayers,
                    TurnManager &turnManager) : eventLoop(loop), totalPlayers(totalPlayers), turnManager(turnManager), EventHandler("PlayerTurnHandler") {};

  void handleEvent(const std::shared_ptr<Event>& event) override;

  std::shared_ptr<PlayerTurnEvent> currentPlayerTurnEvent;

private:
  std::shared_ptr<EventLoop> eventLoop;
  int totalPlayers;
  TurnManager &turnManager;
};

#endif // !PLAYER_TURN_EVENT_H
