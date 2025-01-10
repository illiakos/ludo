#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "EventLoop.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include "PlayerTurnEvent.hpp"

class TurnManager {
public:
  // Deleted default constructor to enforce the use of setInstance
  TurnManager(const TurnManager &) = delete;
  TurnManager &operator=(const TurnManager &) = delete;

  // Access the singleton instance
  static TurnManager &getInstance();

  // Set the singleton instance manually
  static void setInstance(TurnManager &instance);

  void startTurn(int startingPlayer, std::function<void()> onGameOver);
  void endTurn();
  int getCurrentPlayerId() const;


  TurnManager(std::shared_ptr<EventLoop> loop);

  int getCurrentRolledValue() {return currentRolledValue;}
  int getPrevRolledValue() {return prevRolledValue;}
  void clearRoll() {currentRolledValue = 0;}
  void setCurrentPlayerTurnEvent(std::shared_ptr<PlayerTurnEvent> event) {
    std::cout << "Setting current player turn event : " << event << std::endl;
    this->event=event;
  };

  std::shared_ptr<PlayerTurnEvent> getCurrentPlayerTurnEvent() {return event;}

private:
  // Constructor remains public for manual creation

  std::shared_ptr<PlayerTurnEvent> event;

  void setCurrentRolledValue(int v) {
    if (currentRolledValue != 0) {
      prevRolledValue = currentRolledValue;
    }
    currentRolledValue = v;
    std::cout << getCurrentRolledValue() << " " << getPrevRolledValue() << std::endl;
  }

  std::shared_ptr<EventLoop> eventLoop;
  int currentPlayerId;
  int totalPlayers;
  std::function<void()> gameOverCallback;

  friend class Dice;

  int currentRolledValue = 0;
  int prevRolledValue = 0;

  void startPlayerTurn();

  static TurnManager *instance; // Singleton instance as a raw pointer
};

#endif // TURN_MANAGER_H
