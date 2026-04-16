#ifndef RENDERER_H_
#define RENDERER_H_

#include "..\DataCenter\Objects\mesh.h"
#include "..\DataCenter\Objects\point.h"
#include "Objects\collisionPacket.h"
#include "Objects\color.h"

class RenderFunctions {
public:
    static CollisionPacket* FindCollision(Point* origin, Point* direction, Mesh* mesh);
    static Color* CalcColor(CollisionPacket* collisionPacket, Point* direction);

private:
    RenderFunctions() = default;
};

#endif