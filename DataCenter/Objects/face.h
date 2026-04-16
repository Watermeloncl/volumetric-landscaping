#ifndef DATA_CENTER_OBJECTS_FACE_H_
#define DATA_CENTER_OBJECTS_FACE_H_

#include "point.h"
#include "..\..\config.h"

class Face {
private:
    Point* corners[4];
    Point* normal;

    FaceType type;
public:
    Face(FaceType type);
    ~Face();

    void Translate(double transX, double transY, double transZ);
    void Rotate(RotationType type, double cosTheta, double sinTheta);
};

#endif