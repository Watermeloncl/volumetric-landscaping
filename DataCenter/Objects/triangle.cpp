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

Point* Triangle::GetNormal() {
    return this->normal;
}

void Triangle::Translate(double transX, double transY, double transZ) {
    for(Point* point : this->points) {
        point->ChangeX(transX);
        point->ChangeY(transY);
        point->ChangeZ(transZ);
    }
}

void Triangle::Rotate(RotationType type, double cosTheta, double sinTheta) {
    for(Point* point : this->points) {
        point->Rotate(type, cosTheta, sinTheta);
    }

    normal->Rotate(type, cosTheta, sinTheta);
    normal->Normalize(); //precaution
}

double Triangle::TestCollision(Point* origin, Point* direction) {
    Point edge1 = Point(
        this->points[1]->GetX() - this->points[0]->GetX(),
        this->points[1]->GetY() - this->points[0]->GetY(),
        this->points[1]->GetZ() - this->points[0]->GetZ()
    );

    Point edge2 = Point(
        this->points[2]->GetX() - this->points[0]->GetX(),
        this->points[2]->GetY() - this->points[0]->GetY(),
        this->points[2]->GetZ() - this->points[0]->GetZ()
    );

    Point h = MathUtilities::CrossProduct(direction, &edge2);
    double determinant = MathUtilities::DotProduct(&edge1, &h);

    if(determinant < RAY_EPSILON) {
        return -1;
    }

    double invDeterminant = 1.0 / determinant;
    Point s = Point(
        origin->GetX() - this->points[0]->GetX(),
        origin->GetY() - this->points[0]->GetY(),
        origin->GetZ() - this->points[0]->GetZ()
    );

    double u = invDeterminant * MathUtilities::DotProduct(&s, &h);
    if((u < 0) || (u > 1)) {
        return -1;
    }

    Point q = MathUtilities::CrossProduct(&s, &edge1);
    double v = invDeterminant * MathUtilities::DotProduct(direction, &q);

    if((v < 0) || ((u + v) > 1)) {
        return -1;
    }

    double t = invDeterminant * MathUtilities::DotProduct(&edge2, &q);
    if(t > RAY_EPSILON) {
        return t;
    } else {
        return -1;
    }
}

std::ostream& operator<<(std::ostream& os, const Triangle& s) {
    os << "(" << *(s.points[0]) << "), (" << *(s.points[1]) << "), (" << *(s.points[2]) << "); (" << *(s.normal) << ")";
    return os;
}
