#include "Dice.hpp"
#include "Color.hpp"
#include "ColorConstants.hpp"
#include "Dimensions.hpp"
#include "EndTurnEvent.hpp"
#include "MapDrawer.hpp"
#include "MovePawnEvent.hpp"
#include "PawnManager.hpp"
#include "TileContext.hpp"
#include "TurnManager.hpp"
#include "stb_image.h"
#include <iostream>

void Dice::renderSelf() const {
  auto &drawer = MapDrawer::getInstance();
  auto &turnManager = TurnManager::getInstance();
  int prevDiceValue = turnManager.getPrevRolledValue();
  int diceValue = turnManager.getCurrentRolledValue();

  if (prevDiceValue == 0 && diceValue == 0) {
    diceValue = 6;
  } else if (diceValue == 0) {
    diceValue = prevDiceValue;
  }

  // Validate dice value
  if (diceValue < 1 || diceValue > 6) {
    std::cerr << "Error: Invalid dice value (" << diceValue << ")."
              << std::endl;
    return;
  }

  // Get the corresponding image path or fallback to test image
  const std::string &imagePath = diceImages[diceValue - 1];

  int width, height, channels;

  // Load image using stb_image
  unsigned char *imageData =
      stbi_load(imagePath.c_str(), &width, &height, &channels, 4);
  if (!imageData) {
    std::cerr << "Failed to load image: " << imagePath << std::endl;
    return;
  }

  Color bgColor = white;

  // if (turnManager.getCurrentRolledValue() != 0) {
  //   switch (turnManager.getCurrentPlayerId()) {
  //   case 1:
  //     bgColor = red;
  //     break;
  //   case 2:
  //     bgColor = green;
  //     break;
  //   case 3:
  //     bgColor = yellow;
  //     break;
  //   case 4:
  //     bgColor = blue;
  //     break;
  //   default:
  //     bgColor = white;
  //     break;
  //   }
  // }

  switch (turnManager.getCurrentPlayerId()) {
    case 1:
      bgColor = red;
      break;
    case 2:
      bgColor = green;
      break;
    case 3:
      bgColor = yellow;
      break;
    case 4:
      bgColor = blue;
      break;
    default:
      bgColor = white;
      break;
    }

  // Render the image
  drawer.drawImageFromData(
      imageData, width, height, channels, drawer.getCellPosition(dimensions.x),
      drawer.getCellPosition(dimensions.y), drawer.getSizeOfCells(1),
      drawer.getSizeOfCells(1), bgColor);

  // Free the image memory
  stbi_image_free(imageData);
}

// TODO: Do some huynia so that it adds some fancy spinning animation and later
// sets currentRolledValue to TurnManager. Example:
//  auto& tm = TurnManager::getInstace();
//  tm.setCurrentRolledValue = some_huynia;
void Dice::onClick() {
  srand(time(nullptr));
  auto &pawnManager = PawnManager::getInstance();
  int random_number =
      std::rand() % 6 + 1; // Generate a random number between 1 and 6
                           //
  auto &turnManager = TurnManager::getInstance();
  if (turnManager.getCurrentRolledValue() != 0) {
    return;
  }
  std::cout << "Random number: " << random_number << std::endl;
  std::cout << "Clicking on dice" << std::endl;
  turnManager.setCurrentRolledValue(random_number);
  bool endTurn = true;
  auto pawns = pawnManager.getPawnsByTeamID(turnManager.currentPlayerId);
  for (size_t i = 0; i < pawns.size(); ++i) {
    // Access the pawn
    auto pawn = pawns[i];

    if (pawn->getContext() == TileContext::Walkable ||
        (pawn->getContext() == TileContext::Finishing && pawn->isActive())) {

      std::cout << "aaaaaaaaaaaaaaaaaaaaaa111111111111111" << std::endl;
      endTurn = false;
      break;
    } else if (pawn->getContext() == TileContext::Base &&
               turnManager.getCurrentRolledValue() == 6) {

      std::cout << "aaaaaaaaaaaaaaaaaaaaaa22222222222222222" << std::endl;
      endTurn = false;
      break;
    }
  }
  if (endTurn) {

    auto event = turnManager.getCurrentPlayerTurnEvent();
    turnManager.clearRoll();
    std::cout << "aaaaaaaaaaaaaaaaaaaaaa" << std::endl;
    event->completeTurn();

    auto eventLoop = EventLoop::getInstance();
    eventLoop->enqueueEvent(std::make_shared<EndTurnEvent>());
  }
}
