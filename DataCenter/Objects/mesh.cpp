#include <iostream>
#include <cmath>

#include "mesh.h"
#include "voxel.h"
#include "triangle.h"
#include "pointCloud.h"
#include "..\..\config.h"

Mesh::Mesh() {
    this->voxels.resize(POINT_CLOUD_WIDTH - 1, std::vector<std::vector<Voxel*>>(POINT_CLOUD_HEIGHT - 1, std::vector<Voxel*>(POINT_CLOUD_DEPTH - 1, nullptr)));

    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                this->voxels[x][y][z] = new Voxel();
            }
        }
    }
}

Mesh::~Mesh() {
    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                delete this->voxels[x][y][z];
            }
        }
    }
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

void Mesh::Translate(double transX, double transY, double transZ) {
    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                this->voxels[x][y][z]->Translate(transX, transY, transZ);
            }
        }
    }
}

void Mesh::Rotate(RotationType type, double theta) {
    double cosTheta = std::cos(theta);
    double sinTheta = std::sin(theta);

    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                this->voxels[x][y][z]->Rotate(type, cosTheta, sinTheta);
            }
        }
    }
}