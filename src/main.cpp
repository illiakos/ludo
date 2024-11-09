#include "Color.h"
#include "EventLoop.h"
#include "EventDispatcher.h"
#include "MovePawnEvent.h"
#include "MovePawnHandler.h"
#include "Player.h"
#include "PlayerTurnEvent.h"
#include "PlayerTurnHandler.h"
#include "RollDiceHandler.h"
#include "StopGameHandler.h"
#include "Team.h"
#include <iostream>
#include <memory>

int main() {
    

    EventDispatcher dispatcher;

    // Create the event loop and pass the dispatcher to it
    EventLoop eventLoop(dispatcher);
    // Create default colors
    Color red("#E4080A");
    Color yellow("#FFDE59");
    Color blue("#0342C8");
    Color green("#7DDA58");

    // Create default teams
    Team teamRed(red, 1);
    Team teamYellow(yellow, 2);
    Team teamBlue(blue, 3);
    Team teamGreen(green, 4);

    // Create default players
    Player redPlayer(1, 1);
    Player yellowPlayer(2,2);
    Player bluePlayer(3,3);
    Player greenPlayer(4,4);

    // Create event handlers
    auto rollDiceHandler = std::make_shared<RollDiceHandler>();
    auto movePawnHandler = std::make_shared<MovePawnHandler>();
    auto stopGameHandler = std::make_shared<StopGameHandler>();
    auto playerTurnHandler = std::make_shared<PlayerTurnHandler>(eventLoop, 4);

    // Subscribe handlers to specific events
    dispatcher.subscribe("RollDiceEvent", rollDiceHandler);
    dispatcher.subscribe("MovePawnEvent", movePawnHandler);
    dispatcher.subscribe("StopGameEvent", stopGameHandler);
    dispatcher.subscribe("PlayerTurnEvent", playerTurnHandler);
    /*eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(1));*/
    /*eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 2, 4));*/
    /*eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(2));*/
    /*eventLoop.enqueueEvent(std::make_shared<StopGameEvent>()); // This will stop the loop*/
    
    eventLoop.enqueueEvent(std::make_shared<PlayerTurnEvent>(1));
    // Process all events in the loop
    std::cout << "Starting game loop...\n";
    eventLoop.processEvents();
    std::cout << "Game loop ended.\n";

    return 0;
}

