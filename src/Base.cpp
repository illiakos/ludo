#include "Base.hpp"
#include "MapDrawer.hpp"
#include <iostream>
#include <string>

void Base::renderSelf () const {
  auto &drawer = MapDrawer::getInstance ();
  drawer.log ();
  drawer.drawBase (dimensions.x, dimensions.y, color);
  return;
}

int Base::getStartingTileId () {
  return startingTileId;
}

Base::~Base () {
}

void Base::skibidi () {
}

std::string Base::toString () {
  return "Base [Team ID: " + std::to_string (teamId)
         + ", Starting Tile ID: " + std::to_string (startingTileId) + "]";
}

bool Base::occupySlot (int slotIndex) {
  if (slotIndex < 0 || slotIndex >= slots.size ()) {
    std::cerr << "Invalid slot index: " << slotIndex << "\n";
    return false;
  }
  if (slots[slotIndex]) {
    std::cerr << "Slot " << slotIndex << " is already occupied!\n";
    return false;
  }
  spawnPoints[slotIndex] = true;
  return true;
}

// Free a slot in the base
bool Base::freeSlot (int slotIndex) {
  if (slotIndex < 0 || slotIndex >= slots.size ()) {
    std::cerr << "Invalid slot index: " << slotIndex << "\n";
    return false;
  }
  if (!slots[slotIndex]) {
    std::cerr << "Slot " << slotIndex << " is already free!\n";
    return false;
  }
  spawnPoints[slotIndex] = false;
  return true;
}

// Check if a slot is occupied
bool Base::isSlotOccupied (int slotIndex) const {
  if (slotIndex < 0 || slotIndex >= slots.size ()) {
    std::cerr << "Invalid slot index: " << slotIndex << "\n";
    return false;
  }
  return slots[slotIndex];
}

int Base::getFirstFreeSlot () const {
  for (int i = 0; i < spawnPoints.size (); ++i) {
    if (!spawnPoints[i]) {
      return i; // Return the index of the first free slot
    }
  }
  return -1; // Return -1 if no free slots are available
}
void Base::initializeSlotCoordinates () {
  slotCoordinates[0] = {1.5f, 3.5f}; // First slot
  slotCoordinates[1] = {3.5f, 3.5f}; // Second slot
  slotCoordinates[2] = {1.5f, 1.5f}; // Third slot
  slotCoordinates[3] = {3.5f, 1.5f}; // Fourth slot
}
std::pair<float, float> Base::getSlotCoordinates (int slotIndex) const {
  if (slotIndex < 0 || slotIndex >= slotCoordinates.size ()) {
    throw std::out_of_range ("Invalid slot index");
  }
  return slotCoordinates[slotIndex];
}
