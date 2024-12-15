#include "Base.hpp"
#include "MapDrawer.hpp"

void Base::renderSelf() const {
  auto drawer = MapDrawer::getInstance();
  drawer.drawBase(dimensions.x, dimensions.y, color);
  return;
}
