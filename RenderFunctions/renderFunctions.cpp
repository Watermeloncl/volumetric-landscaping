#include "RenderFunctions.h"
#include "..\DataCenter\Objects\triangle.h"
#include "..\DataCenter\Objects\voxel.h"
#include "..\DataCenter\Objects\point.h"
#include "..\DataCenter\Objects\mesh.h"
#include "Objects\voxelGenerator.h"
#include "Objects\collisionPacket.h"
#include "Objects\color.h"
#include "Objects\lights.h"


CollisionPacket* RenderFunctions::FindCollision(Point* origin, Point* direction, VoxelGenerator* generator) {
    Voxel* currVoxel = generator->FindFirstVoxel();

    while(currVoxel != nullptr) {
        CollisionPacket* hit = currVoxel->FindCollision(origin, direction);
        if(hit == nullptr) {
            currVoxel = generator->FindNextVoxel();
        } else {
            return hit;
        }
    }

    return nullptr;
}

Color* RenderFunctions::CalcColor(CollisionPacket* collisionPacket, Point* direction, Lights* lights) {
    /*
    CalcColor(triangle, direction, lights)
    - translate normal into texture
    - translate collision point into color
    - determine phong shading
    - return pixel color (fraction)
    
    */
    if(collisionPacket == nullptr) {
        return new Color(lights->GetBackground());
    }

    return new Color(0, 0.3, 0.85);
}

