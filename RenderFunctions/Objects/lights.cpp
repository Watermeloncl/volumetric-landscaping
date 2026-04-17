#include "lights.h"

Lights::Lights() {

}

Lights::Lights(Color* background, Color* ambient, Color* lightColor, Point* lightDirection) {
    this->background = background;
    this->ambient = ambient;
    this->lightColor = lightColor;
    this->lightDirection = lightDirection;
}

Lights::~Lights() {
    delete this->background;
    delete this->ambient;
    delete this->lightColor;
    delete this->lightDirection;
}

Color* Lights::GetBackground() {
    return this->background;
}

Color* Lights::GetAmbient() {
    return this->ambient;
}

Color* Lights::GetLightColor() {
    return this->lightColor;
}

Point* Lights::GetLightDirection() {
    return this->lightDirection;
}
