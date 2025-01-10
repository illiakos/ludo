#include "Dice.hpp"
#include "Color.hpp"
#include "Dimensions.hpp"
#include "MapDrawer.hpp"
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
    if (diceValue < 1|| diceValue > 6) {
        std::cerr << "Error: Invalid dice value (" << diceValue << ")." << std::endl;
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

    // Render the image
    drawer.drawImageFromData(imageData, width, height, channels,
                             drawer.getCellPosition(dimensions.x),
                             drawer.getCellPosition(dimensions.y),
                             drawer.getSizeOfCells(1), drawer.getSizeOfCells(1));

    // Free the image memory
    stbi_image_free(imageData);
}

// TODO: Do some huynia so that it adds some fancy spinning animation and later
// sets currentRolledValue to TurnManager. Example:
//  auto& tm = TurnManager::getInstace();
//  tm.setCurrentRolledValue = some_huynia;
void Dice::onClick() {
  srand(time(nullptr));
  auto &turnManager = TurnManager::getInstance();
  int random_number = std::rand() % 6 + 1; // Generate a random number between 1 and 6
  std::cout << "Random number: " << random_number << std::endl;
  std::cout << "Clicking on dice" << std::endl;
  turnManager.setCurrentRolledValue(random_number);
}
