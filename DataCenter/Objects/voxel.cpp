#include "voxel.h"
#include "triangle.h"

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