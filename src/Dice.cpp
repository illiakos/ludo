#include "Dice.hpp"
#include "Color.hpp"
#include "Dimensions.hpp"
#include "MapDrawer.hpp"
#include "TurnManager.hpp"
#include <iostream>

/*Dice::Dice(Dimensions d) : dimensions(d) {}*/

void Dice::renderSelf() const {
  // TODO: Implement dice rendering mechanic. Probably gonna have to use images,
  // or
  //  you can use large switch/case where for each value (1-6) you would have to
  //  create custom rendering
  auto &drawer = MapDrawer::getInstance();
  auto &turnManager = TurnManager::getInstance();
  auto randomColor = Color(0.18594f, 0.45182f, 0.92725f);
  if (turnManager.getCurrentRolledValue() > 3) {
    randomColor = Color(0.97525f, 0.124f, 0.5672f);
  }
  
  std::cout << "Current turn holder : " << turnManager.getCurrentPlayerId() << std::endl;

  drawer.drawRectangle(drawer.getCellPosition(dimensions.x),
                       drawer.getCellPosition(dimensions.y),
                       drawer.getSizeOfCells(1), drawer.getSizeOfCells(1),
                       randomColor);
}

// TODO: Do some huynia so that it adds some fancy spinning animation and later
// sets currentRolledValue to TurnManager. Example:
//  auto& tm = TurnManager::getInstace();
//  tm.setCurrentRolledValue = some_huynia;
void Dice::onClick() {
  auto &turnManager = TurnManager::getInstance();
  int random_number =
      std::rand() % 6 + 1; // Generate a random number between 1 and 6
  std::cout << "Random number: " << random_number << std::endl;
  std::cout << "Clicking on dice" << std::endl;
  turnManager.setCurrentRolledValue(random_number);
}
