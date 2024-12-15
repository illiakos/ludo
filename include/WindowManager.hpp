#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

class WindowManager {
public:
    static WindowManager &getInstance();

    void setWindowSize(int width, int height);
    std::pair<int, int> getWindowSize(); // Return window size as a pair

private:
    WindowManager() : windowWidth(800), windowHeight(600) {}
    int windowWidth;
    int windowHeight;
};

#endif // WINDOW_MANAGER_HPP
