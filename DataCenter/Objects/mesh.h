#ifndef DATA_CENTER_MESH_H_
#define DATA_CENTER_MESH_H_

#include <vector>

#include "pointCloud.h"
#include "voxel.h"
#include "triangle.h"
#include "..\..\config.h"

class Mesh {
private:
    std::vector<std::vector<std::vector<Voxel*>>> voxels;

    int triangleCount = 0;

public:
    Mesh();
    ~Mesh();

    void SetVoxel(int x, int y, int z, Voxel* newVoxel);
    Voxel* GetVoxel(int x, int y, int z);

    void AddTriangle(int x, int y, int z, Triangle* newTriangle);
    
    void IncrementTriangleCount();
    int GetTriangleCount();

    void Translate(double transX, double transY, double transZ);
    void Rotate(RotationType type, double theta);
};

#endif