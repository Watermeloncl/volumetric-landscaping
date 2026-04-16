#ifndef RENDER_FUNCTIONS_OBJECTS_COLLISION_PACKET_H_
#define RENDER_FUNCTIONS_OBJECTS_COLLISION_PACKET_H_

#include "..\..\DataCenter\Objects\triangle.h"
#include "..\..\DataCenter\Objects\point.h"

class CollisionPacket {
private:
    Triangle* triangle;
    Point* collisionPoint;

public:
    CollisionPacket();
    CollisionPacket(Triangle* triangle, Point* collisionPoint);
    ~CollisionPacket();

    void SetCollisionPoint(Point* newCollisionPoint);
    Point* GetCollisionPoint();
};

#endif