#ifndef RENDERER_H_
#define RENDERER_H_

#include "..\DataCenter\Objects\point.h"
#include "Objects\collisionPacket.h"
#include "Objects\color.h"
#include "Objects\lights.h"
#include "Objects\voxelGenerator.h"

class RenderFunctions {
public:
    static CollisionPacket* FindCollision(Point* origin, Point* direction, VoxelGenerator* generator);
    static Color* CalcColor(CollisionPacket* collisionPacket, Point* direction, Lights* lights);

private:
    RenderFunctions() = default;
};

#endif