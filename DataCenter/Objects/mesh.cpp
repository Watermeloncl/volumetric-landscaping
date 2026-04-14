#include <iostream>

#include "mesh.h"
#include "voxel.h"
#include "triangle.h"
#include "pointCloud.h"
#include "..\..\config.h"

Mesh::Mesh() {
    this->voxels.resize(POINT_CLOUD_SIZE - 1, std::vector<std::vector<Voxel*>>(POINT_CLOUD_SIZE - 1, std::vector<Voxel*>(POINT_CLOUD_SIZE - 1, new Voxel())));
}

Mesh::~Mesh() {

}

void Mesh::SetVoxel(int x, int y, int z, Voxel* newVoxel) {
    this->voxels[x][y][z] = newVoxel;
}

Voxel* Mesh::GetVoxel(int x, int y, int z) {
    return this->voxels[x][y][z];
}

void Mesh::AddTriangle(int x, int y, int z, Triangle* newTriangle) {
    this->voxels[x][y][z]->AddTriangle(newTriangle);
}

void Mesh::IncrementTriangleCount() {
    (this->triangleCount)++;
}

int Mesh::GetTriangleCount() {
    return this->triangleCount;
}
