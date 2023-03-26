#include "color.h"

Color::Color(double red, double green, double blue) : Red(red), Green(green), Blue(blue) {
}

void Color::Values(double new_red, double new_green, double new_blue) {
    Red = new_red;
    Green = new_green;
    Blue = new_blue;
}