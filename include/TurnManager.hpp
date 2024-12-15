#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "EventLoop.hpp"
#include <functional>

class TurnManager {
public:
    TurnManager(EventLoop& loop);

    void startTurn(int startingPlayer, std::function<void()> onGameOver);
    void endTurn();

    int getCurrentPlayerId() const;

private:
    EventLoop& eventLoop;
    int currentPlayerId;
    int totalPlayers;
    std::function<void()> gameOverCallback;

    void startPlayerTurn();
};

#endif // TURN_MANAGER_H
