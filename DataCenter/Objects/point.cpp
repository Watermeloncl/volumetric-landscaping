#include <iostream>

#include "point.h"

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

void Point::SetY(double newY) {
    this->y = newY;
}

double Point::GetY() {
    return this->y;
}

void Point::SetZ(double newZ) {
    this->z = newZ;
}

double Point::GetZ() {
    return this->z;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << p.x << " " << p.y << " " << p.z;
    return os;
}