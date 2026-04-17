#ifndef RENDER_FUNCTIONS_OBJECTS_VOXEL_GENERATOR_H_
#define RENDER_FUNCTIONS_OBJECTS_VOXEL_GENERATOR_H_

#include "..\..\DataCenter\Objects\point.h"
#include "..\..\DataCenter\Objects\voxel.h"
#include "..\..\DataCenter\Objects\mesh.h"
#include "..\..\Utilities\matrix.h"

class VoxelGenerator {
private:
    Mesh* mesh = nullptr;
    Point* origin = nullptr;
    Point* direction = nullptr;
    Point* currPoint = nullptr;
    
    Point* tDelta = nullptr;
    Point* tMax = nullptr;

    // I didn't make the int ones points...
    int stepX;
    int stepY;
    int stepZ;

    int xIndex;
    int yIndex;
    int zIndex;

public:
    VoxelGenerator();
    ~VoxelGenerator();

    void SeedMesh(Mesh* mesh);
    void SeedRays(Point* origin, Point* direction);
    void PopulateTMax();
    Voxel* FindFirstVoxel();
    Voxel* FindNextVoxel();
};

#endif