#include "EventLoop.h"
#include "EventDispatcher.h"
#include "MovePawnEvent.h"
#include "MovePawnHandler.h"
#include "RollDiceEvent.h"
#include "RollDiceHandler.h"
#include "StopGameEvent.h"
#include "StopGameHandler.h"
#include <iostream>
#include <memory>

int main() {
    EventDispatcher dispatcher;

    // Create event handlers
    auto rollDiceHandler = std::make_shared<RollDiceHandler>();
    auto movePawnHandler = std::make_shared<MovePawnHandler>();
    auto stopGameHandler = std::make_shared<StopGameHandler>();

    // Subscribe handlers to specific events
    dispatcher.subscribe("RollDiceEvent", rollDiceHandler);
    dispatcher.subscribe("MovePawnEvent", movePawnHandler);
    dispatcher.subscribe("StopGameEvent", stopGameHandler);

    // Create the event loop and pass the dispatcher to it
    EventLoop eventLoop(dispatcher);

    // Enqueue some sample events
    eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(1));
    eventLoop.enqueueEvent(std::make_shared<MovePawnEvent>(1, 2, 4));
    eventLoop.enqueueEvent(std::make_shared<RollDiceEvent>(2));
    eventLoop.enqueueEvent(std::make_shared<StopGameEvent>()); // This will stop the loop

    // Process all events in the loop
    std::cout << "Starting game loop...\n";
    eventLoop.processEvents();
    std::cout << "Game loop ended.\n";

    return 0;
}

