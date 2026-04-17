#include <cmath>

#include "RenderFunctions.h"
#include "..\DataCenter\Objects\triangle.h"
#include "..\DataCenter\Objects\voxel.h"
#include "..\DataCenter\Objects\point.h"
#include "..\DataCenter\Objects\mesh.h"
#include "Objects\voxelGenerator.h"
#include "Objects\collisionPacket.h"
#include "Objects\color.h"
#include "Objects\lights.h"
#include "..\Utilities\mathUtilities.h"


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

    // determine colors based on texture map. For now, just use... dark green. Haha.
    double odr = 0.2196;
    double odg = 0.7843;
    double odb = 0.3725;

    double osr = 0.2196;
    double osg = 0.7843;
    double osb = 0.3725;

    //start of color
    double r = 0;
    double g = 0;
    double b = 0;

    r += (Ka * lights->GetAmbient()->GetRed() * odr);
    g += (Ka * lights->GetAmbient()->GetGreen() * odg);
    b += (Ka * lights->GetAmbient()->GetBlue() * odb);

    if(RenderFunctions::InShadow(collisionPacket->GetCollisionPoint(), lights)) {
        return new Color(r, g, b);
    }

    Point* normal = collisionPacket->GetTriangle()->GetNormal();
    double nl = MathUtilities::DotProduct(normal, lights->GetLightDirection());
    if(nl < 0) {
        return new Color(r, g, b);
    }

    r += (lights->GetLightColor()->GetRed() * Kd * odr * nl);
    g += (lights->GetLightColor()->GetGreen() * Kd * odg * nl);
    b += (lights->GetLightColor()->GetBlue() * Kd * odb * nl);
    
    Point reflectVector = Point(
        2 * nl * normal->GetX(),
        2 * nl * normal->GetY(),
        2 * nl * normal->GetZ()     
    );

    Point negativeDirection = Point(
        -direction->GetX(),
        -direction->GetY(),
        -direction->GetZ()
    );

    double rv = MathUtilities::DotProduct(&reflectVector, &negativeDirection);        
    if(rv < 0) {
        rv = 0;
    } else {
        rv = std::pow(rv, Kgls);
    }

    r += (lights->GetLightColor()->GetRed() * Ks * osr * rv);
    g += (lights->GetLightColor()->GetGreen() * Ks * osg * rv);
    b += (lights->GetLightColor()->GetBlue() * Ks * osb * rv);

    return new Color(r, g, b);
}

bool RenderFunctions::InShadow(Point* CollisionPoint, Lights* lights) {
    // shoot... TODO
    // transform ray off inverse matrix
    // voxel traverse until we get out
    return false;
}
