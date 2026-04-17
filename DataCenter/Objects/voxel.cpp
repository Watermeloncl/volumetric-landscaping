#include <vector>
#include <cfloat>

#include "voxel.h"
#include "triangle.h"
#include "..\..\RenderFunctions\Objects\collisionPacket.h"
#include "..\..\config.h"

Voxel::Voxel() {
    
}

Voxel::~Voxel() {

}

bool Voxel::HasTriangles() {
    return this->polygons.size() != 0;
}

void Voxel::AddTriangle(Triangle* newTriangle) {
    this->polygons.push_back(newTriangle);
}

void Voxel::Translate(double transX, double transY, double transZ) {
    for(Triangle* triangle : this->polygons) {
        triangle->Translate(transX, transY, transZ);
    }
}

void Voxel::Rotate(RotationType type, double cosTheta, double sinTheta) {
    for(Triangle* triangle : this->polygons) {
        triangle->Rotate(type, cosTheta, sinTheta);
    }
}

CollisionPacket* Voxel::FindCollision(Point* origin, Point* direction) {
    if(!this->HasTriangles()) {
        return nullptr;
    }

    double minDist = DBL_MAX;
    int index = -1;
    for(int i = 0; i < (int)this->polygons.size(); i++) {
        double t = this->polygons[i]->TestCollision(origin, direction);
        if((t < 0) || (t > minDist)) {
            continue;
        } else {
            index = i;
            minDist = t;
        }
    }

    if(index == -1) {
        return nullptr;
    }

    return new CollisionPacket(
        this->polygons[index],
        new Point(
            origin->GetX() + (direction->GetX() * minDist),
            origin->GetY() + (direction->GetY() * minDist),
            origin->GetZ() + (direction->GetZ() * minDist)
        )
    );
}