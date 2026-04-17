#ifndef DATA_CENTER_OBJECTS_TRIANGLE_H_
#define DATA_CENTER_OBJECTS_TRIANGLE_H_

#include <iostream>

#include "point.h"
#include "..\..\config.h"

class Triangle {
private:
    Point* points[3];
    Point* normal = nullptr;
    Point* trueVoxel = nullptr;
public:
    Triangle(Point* point0, Point* point1, Point* point2, Point* voxelCoords);
    ~Triangle();

    void SetNormal();
    Point* GetNormal();
    double GetElevationHeight();

    void Translate(double transX, double transY, double transZ);
    void Rotate(RotationType type, double cosTheta, double sinTheta);

    double TestCollision(Point* origin, Point* direction);
    friend std::ostream& operator<<(std::ostream& os, const Triangle& s);

};

#endif