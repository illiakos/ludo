

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Dimensions.hpp"
#include <memory>
class MapDrawer;

class Renderable {
public:
  virtual void renderSelf() const = 0;
  virtual ~Renderable() = default;
  virtual const Dimensions &getDimensions() const = 0;

  // Getter for z-index
  virtual int getZIndex() const = 0;

  // Setter for z-index
  virtual void setZIndex(int z) = 0;

  virtual void onClick() = 0;

};
class RenderableContainer {
public:
  virtual void addRenderable(const std::shared_ptr<Renderable> r) = 0;
  ~RenderableContainer();
};
#endif // !RENDERABLE_H
