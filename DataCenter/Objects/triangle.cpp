#include <iostream>
#include <cmath>

#include "triangle.h"
#include "point.h"
#include "..\..\Utilities\mathUtilities.h"
#include "..\..\config.h"

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

    double x1 = points[1]->GetX() - points[0]->GetX();
    double y1 = points[1]->GetY() - points[0]->GetY();
    double z1 = points[1]->GetZ() - points[0]->GetZ();
    
    double x2 = points[2]->GetX() - points[1]->GetX();
    double y2 = points[2]->GetY() - points[1]->GetY();
    double z2 = points[2]->GetZ() - points[1]->GetZ();

    double nx = (y1*z2) - (z1*y2);
    double ny = -((x1*z2) - (z1*x2));
    double nz = (x1*y2) - (y1*x2);

    MathUtilities::Normalize(nx, ny, nz);

    this->normal->SetX(nx);
    this->normal->SetY(ny);
    this->normal->SetZ(nz);
}

void Triangle::Translate(double transX, double transY, double transZ) {
    for(Point* point : this->points) {
        point->ChangeX(transX);
        point->ChangeY(transY);
        point->ChangeZ(transZ);
    }

    normal->ChangeX(transX);
    normal->ChangeY(transY);
    normal->ChangeZ(transZ);
}

void Triangle::Rotate(RotationType type, double cosTheta, double sinTheta) {
    for(Point* point : this->points) {
        point->Rotate(type, cosTheta, sinTheta);
    }

    normal->Rotate(type, cosTheta, sinTheta);
}