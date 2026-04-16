#include "color.h"

Color::Color() {

}

Color::Color(double red, double green, double blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Color::~Color() {

}

void Color::SetRed(double newRed) {
    this->red = newRed;
}

double Color::GetRed() {
    return this->red;
}

void Color::SetGreen(double newGreen) {
    this->green = newGreen;
}

double Color::GetGreen() {
    return this->green;
}

void Color::SetBlue(double newBlue) {
    this->blue = newBlue;
}

double Color::GetBlue() {
    return this->blue;
}
