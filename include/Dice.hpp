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
  int zIndex=3;
  std::string diceImages[6] = {
    "../src/assets/images/one.png",
    "../src/assets/images/two.png",
    "../src/assets/images/three.png",
    "../src/assets/images/four.png",
    "../src/assets/images/five.png",
    "../src/assets/images/six.png"
  };

};

#endif // !DICE_HPP
