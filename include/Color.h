#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class Color {
public:
    // Constructor from RGB values
    Color(int r, int g, int b) : red(r), green(g), blue(b) {}

    // Constructor from float RGB values
    Color(float r, float g, float b) : redf(r), greenf(g), bluef(b) {}

    // Constructor from hex string (e.g., "#FF5733" or "FF5733")
    Color(const std::string& hexCode) {
        if (hexCode[0] == '#') {
            fromHex(hexCode.substr(1)); // Remove leading '#' if present
        } else {
            fromHex(hexCode);
        }
    }

    // Getters for each color component
    int getRed() const { return red; }
    int getGreen() const { return green; }
    int getBlue() const { return blue; }

    float getRedf() const { return redf; }
    float getGreenf() const { return greenf; }
    float getBluef() const { return bluef; }

    // Convert RGB to hex string
    std::string toHex() const {
        std::stringstream ss;
        ss << "#" << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << red
           << std::setw(2) << std::setfill('0') << green
           << std::setw(2) << std::setfill('0') << blue;
        return ss.str();
    }

private:
    int red, green, blue;
    float redf, greenf, bluef;

    // Convert a hex string (e.g., "FF5733") to RGB values
    void fromHex(const std::string& hex) {
        if (hex.size() != 6) {
            throw std::invalid_argument("Invalid hex code format");
        }
        red = std::stoi(hex.substr(0, 2), nullptr, 16);
        green = std::stoi(hex.substr(2, 2), nullptr, 16);
        blue = std::stoi(hex.substr(4, 2), nullptr, 16);
    }
};

#endif
