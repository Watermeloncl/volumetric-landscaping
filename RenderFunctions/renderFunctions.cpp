#include <cmath>

#include "RenderFunctions.h"
#include "..\DataCenter\Objects\triangle.h"
#include "..\DataCenter\Objects\voxel.h"
#include "..\DataCenter\Objects\point.h"
#include "..\DataCenter\Objects\mesh.h"
#include "..\DataCenter\Objects\worldData.h"
#include "Objects\voxelGenerator.h"
#include "Objects\collisionPacket.h"
#include "Objects\color.h"
#include "Objects\lights.h"
#include "Objects\texture.h"
#include "..\Utilities\mathUtilities.h"
#include "..\config.h"

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

Color* RenderFunctions::CalcColor(CollisionPacket* collisionPacket, Point* direction, Lights* lights, Texture** textures, WorldData* worldData) {
    if(collisionPacket == nullptr) {
        return new Color(lights->GetBackground());
    }

    Point* collisionPoint = collisionPacket->GetCollisionPoint();
    Point* normal = collisionPacket->GetTriangle()->GetNormal();

    // determine colors based on texture map. Otherwise, use green.
    double odr, odg, odb, osr, osg, osb;
    if(worldData->TEXTURES_ON) {
        int index;
        if((collisionPacket->GetTriangle()->GetElevationHeight() < worldData->SAND_LEVEL) && (normal->GetY() > worldData->GRASS_LEVEL)) {
            index = 3;
        } else if(normal->GetY() > worldData->GRASS_LEVEL) {
            index = 1;
        } else if(normal->GetY() > worldData->ROCK_LEVEL) {
            index = 2;
        } else {
            index = 0;
        }

        Color textureColor = textures[index]->SampleTexture(collisionPoint, normal);

        odr = textureColor.GetRed();
        odg = textureColor.GetGreen();
        odb = textureColor.GetBlue();

        osr = textureColor.GetRed();
        osg = textureColor.GetGreen();
        osb = textureColor.GetBlue();
    } else {
        odr = worldData->ALT_COLOR_R;
        odg = worldData->ALT_COLOR_G;
        odb = worldData->ALT_COLOR_B;

        osr = worldData->ALT_COLOR_R;
        osg = worldData->ALT_COLOR_G;
        osb = worldData->ALT_COLOR_B;
    }

    //start of color
    double r = 0;
    double g = 0;
    double b = 0;

    r += (worldData->Ka * lights->GetAmbient()->GetRed() * odr);
    g += (worldData->Ka * lights->GetAmbient()->GetGreen() * odg);
    b += (worldData->Ka * lights->GetAmbient()->GetBlue() * odb);

    if(RenderFunctions::InShadow(collisionPoint, lights)) {
        return new Color(r, g, b);
    }

    double nl = MathUtilities::DotProduct(normal, lights->GetLightDirection());
    if(nl < 0) {
        return new Color(r, g, b);
    }

    r += (lights->GetLightColor()->GetRed() * worldData->Kd * odr * nl);
    g += (lights->GetLightColor()->GetGreen() * worldData->Kd * odg * nl);
    b += (lights->GetLightColor()->GetBlue() * worldData->Kd * odb * nl);
    
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
        rv = std::pow(rv, worldData->Kgls);
    }

    r += (lights->GetLightColor()->GetRed() * worldData->Ks * osr * rv);
    g += (lights->GetLightColor()->GetGreen() * worldData->Ks * osg * rv);
    b += (lights->GetLightColor()->GetBlue() * worldData->Ks * osb * rv);

    return new Color(r, g, b);
}

bool RenderFunctions::InShadow(Point* CollisionPoint, Lights* lights) {
    // shoot... TODO?
    // transform ray off inverse matrix
    // voxel traverse until we get out
    return false;
}
