#ifndef DICE_HPP
#define DICE_HPP

#include "Dimensions.hpp"
#include "Renderable.hpp"
class Dice : public Renderable {
public:
  Dice(Dimensions d) : dimensions(d) {};


  void renderSelf() const override;
  void onClick() override; 

  int getZIndex() const override {return zIndex;}

  void setZIndex(int z) override {zIndex = z;}
  const Dimensions& getDimensions() const override {return dimensions;}

private:
  Dimensions dimensions;
  int zIndex=2;

};

#endif // !DICE_HPP
