

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>
class MapDrawer;


class Renderable {
public:
  virtual void renderSelf() const = 0;
  virtual ~Renderable() = default;
  
};

class RenderableContainer {
public:
  virtual void addRenderable(const std::shared_ptr<Renderable> r);
};
#endif // !RENDERABLE_H
