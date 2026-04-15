#include <iostream>

#include "point.h"
#include "..\..\Utilities\mathUtilities.h"
#include "..\..\config.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(Point* point) {
    this->x = point->x;
    this->y = point->y;
    this->z = point->z;
}

Point::~Point() {

}

void Point::SetX(double newX) {
    this->x = newX;
}

double Point::GetX() {
    return this->x;
}

void Point::ChangeX(double deltaX) {
    this->x += deltaX;
}

void Point::SetY(double newY) {
    this->y = newY;
}

double Point::GetY() {
    return this->y;
}

void Point::ChangeY(double deltaY) {
    this->y += deltaY;
}

void Point::SetZ(double newZ) {
    this->z = newZ;
}

double Point::GetZ() {
    return this->z;
}

void Point::ChangeZ(double deltaZ) {
    this->z += deltaZ;
}

void Point::Rotate(RotationType type, double cosTheta, double sinTheta) {
    MathUtilities::RotateCoordinate(type, this->x, this->y, this->z, cosTheta, sinTheta);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << p.x << " " << p.y << " " << p.z;
    return os;
}