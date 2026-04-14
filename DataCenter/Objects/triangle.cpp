#include <cmath>

#include "triangle.h"
#include "point.h"

Triangle::Triangle(Point* point0, Point* point1, Point* point2) {
    this->points[0] = point0;
    this->points[1] = point1;
    this->points[2] = point2;

    this->SetNormal();
}

Triangle::~Triangle() {
    delete this->normal;
}

void Triangle::SetNormal() {
    this->normal = new Point();

    double ax = points[2]->GetX() - points[0]->GetX();
    double ay = points[2]->GetY() - points[0]->GetY();
    double az = points[2]->GetZ() - points[0]->GetZ();
    
    double bx = points[1]->GetX() - points[0]->GetX();
    double by = points[1]->GetY() - points[0]->GetY();
    double bz = points[1]->GetZ() - points[0]->GetZ();

    double nx = (ay * bz) - (az * by);
    double ny = (az * bx) - (ax * bz);
    double nz = (ax * by) - (ay * bx);

    //TODO change to math function normalize
    double invMag = 1 / std::sqrt(nx*nx + ny*ny + nz*nz);
    nx *= invMag;
    ny *= invMag;
    nz *= invMag;

    this->normal->SetX(nx);
    this->normal->SetY(ny);
    this->normal->SetZ(nz);
}