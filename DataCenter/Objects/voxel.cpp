#include <vector>

#include "voxel.h"
#include "triangle.h"
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