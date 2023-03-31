#pragma once

#include <cstdint>

struct Color {
    Color() = default;
    Color(double red, double green, double blue);
    void Values(double new_red, double new_green, double new_blue);
    double Red = 0;
    double Green = 0;
    double Blue = 0;
};