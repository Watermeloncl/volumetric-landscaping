#ifndef DATA_CENTER_OBJECTS_VOXEL_H_
#define DATA_CENTER_OBJECTS_VOXEL_H_

#include <vector>

#include "triangle.h"
#include "..\..\config.h"

class Voxel {
private:
    std::vector<Triangle*> polygons;

public:
    Voxel();
    ~Voxel();

    bool HasTriangles();
    void AddTriangle(Triangle* newTriangle);
    
    void Translate(double transX, double transY, double transZ);
    void Rotate(RotationType type, double cosTheta, double sinTheta);
};

#endif