#include "ClickHandler.hpp"
#include <iostream>

std::unordered_map<GLFWwindow*, ClickHandler*> ClickHandler::instances;

ClickHandler::ClickHandler(GLFWwindow* window) : window(window), cursorX(0), cursorY(0) {
    instances[window] = this;
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
}

ClickHandler::~ClickHandler() {
    instances.erase(window);
}

void ClickHandler::registerClickCallback(int button, ClickCallback callback) {
    callbacks[button] = callback;
}

void ClickHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto it = instances.find(window);
    if (it != instances.end()) {
        it->second->handleMouseButton(button, action, mods);
    }
}

void ClickHandler::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    auto it = instances.find(window);
    if (it != instances.end()) {
        it->second->handleCursorPosition(xpos, ypos);
    }
}

void ClickHandler::handleMouseButton(int button, int action, int mods) {
    if (action == GLFW_PRESS && callbacks.find(button) != callbacks.end()) {
        callbacks[button](cursorX, cursorY);
    }
}

void ClickHandler::handleCursorPosition(double xpos, double ypos) {
    cursorX = xpos;
    cursorY = ypos;
}
