#ifndef RENDER_FUNCTIONS_OBJECTS_LIGHTS_H_
#define RENDER_FUNCTIONS_OBJECTS_LIGHTS_H_

#include "color.h"
#include "..\..\DataCenter\Objects\point.h"

class Lights {
private:
    Color* background = nullptr;
    Color* ambient = nullptr;
    Color* lightColor = nullptr;
    Point* lightDirection = nullptr;

public:
    Lights();
    Lights(Color* background, Color* ambient, Color* lightColor, Point* lightDirection);
    ~Lights();

    Color* GetBackground();
    Color* GetAmbient();
    Color* GetLightColor();
    Point* GetLightDirection();
};

#endif