#ifndef RENDER_FUNCTIONS_OBJECTS_TEXTURE_H_
#define RENDER_FUNCTIONS_OBJECTS_TEXTURE_H_

#include "..\..\DataCenter\Objects\point.h"
#include "color.h"

class Texture {
private:
    int width, height;
    unsigned char* data = nullptr;
public:
    Texture(const char* textureName);
    ~Texture();

    Color SampleTexture(Point* collisionPoint, Point* normal);
};

#endif
