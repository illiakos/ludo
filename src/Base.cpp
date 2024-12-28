#include "Base.hpp"
#include "MapDrawer.hpp"
#include <iostream>

void Base::renderSelf() const {
  auto drawer = MapDrawer::getInstance();
  drawer.log();
  cout << "SHTRING" << endl;
  Color red = Color(0.996f, 0.180f, 0.090f);
  drawer.drawBase(0, 9, red);
  return;
}

Base::~Base() {

}

void Base::skibidi() {
  std::cout << "SHKIBIDI" << endl;
}
