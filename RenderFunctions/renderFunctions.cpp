#include "RenderFunctions.h"
#include "..\DataCenter\Objects\triangle.h"
#include "..\DataCenter\Objects\point.h"
#include "..\DataCenter\Objects\mesh.h"
#include "Objects\collisionPacket.h"
#include "Objects\color.h"


CollisionPacket* RenderFunctions::FindCollision(Point* origin, Point* direction, Mesh* mesh) {
    return nullptr;
}

Color* RenderFunctions::CalcColor(CollisionPacket* collisionPacket, Point* direction) {
    if(collisionPacket == nullptr) {
        return new Color(0, 0.3, 0.85);
    }

    return new Color(0, 0.3, 0.85);
}