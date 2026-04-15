#ifndef DATA_CENTER_OBJECTS_TRIANGLE_H_
#define DATA_CENTER_OBJECTS_TRIANGLE_H_

#include "point.h"
#include "..\..\config.h"

class Triangle {
private:
    Point* points[3];
    Point* normal = nullptr;
public:
    Triangle(Point* point0, Point* point1, Point* point2);
    ~Triangle();

    void SetNormal();

    void Translate(double transX, double transY, double transZ);
    void Rotate(RotationType type, double cosTheta, double sinTheta);
};

#endif