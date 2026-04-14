#ifndef DATA_CENTER_OBJECTS_POINT_H_
#define DATA_CENTER_OBJECTS_POINT_H_

#include <iostream>

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

    void SetY(double newY);
    double GetY();

    void SetZ(double newZ);
    double GetZ();

    friend std::ostream& operator<<(std::ostream& os, const Point& s);
};

#endif