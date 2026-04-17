#ifndef DATA_CENTER_OBJECTS_POINT_H_
#define DATA_CENTER_OBJECTS_POINT_H_

#include <iostream>

#include "..\..\config.h"

class Point {
private:
    double x;
    double y;
    double z;
public:
    Point();
    Point(double x, double y, double z);
    Point(Point* point);
    ~Point();

    void SetX(double newX);
    double GetX();
    void ChangeX(double deltaX);

    void SetY(double newY);
    double GetY();
    void ChangeY(double deltaY);

    void SetZ(double newZ);
    double GetZ();
    void ChangeZ(double deltaZ);

    void Rotate(RotationType type, double cosTheta, double sinTheta);

    void Normalize();
    void ReplaceValues(double* newValues);
    void ReplaceValues(Point* point);
    void ReplaceValues(double newX, double newY, double newZ);

    friend std::ostream& operator<<(std::ostream& os, const Point& s);
};

#endif