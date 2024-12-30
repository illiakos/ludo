#ifndef BASE_H
#define BASE_H

#include "Color.hpp"
#include "Dimensions.hpp"
#include "Renderable.hpp"
#include "Tile.hpp"
#include <array>
#include <string>
#include <vector>
class Base : public Renderable {

public:
  Base (Dimensions dimensions, Color color, int teamId, int startingTileId)
      : dimensions (dimensions), color (color), teamId (teamId), startingTileId (startingTileId) {

    spawnPoints.fill (false);
    initializeSlotCoordinates ();
  };
  virtual void renderSelf () const override;
  ~Base ();
  void skibidi ();
  std::string toString ();
  int getStartingTileId ();
  Dimensions getDimensions () { return dimensions; };
  int getTeamId () { return teamId; }

  bool occupySlot (int slotIndex);
  bool freeSlot (int slotIndex);
  bool isSlotOccupied (int slotIndex) const;
  int getFirstFreeSlot () const; // Method to get the first free slot
  std::pair<float, float> getSlotCoordinates (int slotIndex) const;

private:
  void initializeSlotCoordinates ();
  std::vector<Tile *> slots;
  Dimensions dimensions;
  Color color;
  int teamId;
  int startingTileId;
  std::array<bool, 4> spawnPoints;

  std::array<std::pair<float, float>, 4> slotCoordinates; // Coordinates for each slot
};

#endif // !BASE_H
