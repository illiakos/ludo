#ifndef CLICK_HANDLER_H
#define CLICK_HANDLER_H

#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>

class ClickHandler {
public:
  using ClickCallback = std::function<void(double x, double y)>;

  ClickHandler(GLFWwindow *window);
  ~ClickHandler();

  void registerClickCallback(int button, ClickCallback callback);

private:
  GLFWwindow *window;
  static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                     double ypos);

  static std::unordered_map<GLFWwindow *, ClickHandler *> instances;
  std::unordered_map<int, ClickCallback> callbacks;
  double cursorX, cursorY;

  void handleMouseButton(int button, int action, int mods);
  void handleCursorPosition(double xpos, double ypos);
};

#endif // CLICK_HANDLER_H
