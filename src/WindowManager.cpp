#include "WindowManager.hpp"

// Singleton instance
WindowManager &WindowManager::getInstance() {
    static WindowManager instance;
    return instance;
}

void WindowManager::setWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

std::pair<int, int> WindowManager::getWindowSize() {
    return {windowWidth, windowHeight};
}
