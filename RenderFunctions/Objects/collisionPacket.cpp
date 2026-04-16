#include "collisionPacket.h"
#include "..\..\DataCenter\Objects\triangle.h"
#include "..\..\DataCenter\Objects\point.h"

CollisionPacket::CollisionPacket() {

}

CollisionPacket::CollisionPacket(Triangle* triangle, Point* collisionPoint) {
    this->triangle = triangle;
    this->collisionPoint = collisionPoint;
}

CollisionPacket::~CollisionPacket() {

}

void CollisionPacket::SetCollisionPoint(Point* newCollisionPoint) {
    this->collisionPoint = newCollisionPoint;
}

Point* CollisionPacket::GetCollisionPoint() {
    return this->collisionPoint;
}
