#include <iostream>
#include <cmath>
#include <cfloat>

#include "voxelGenerator.h"
#include "..\..\DataCenter\Objects\mesh.h"
#include "..\..\DataCenter\Objects\voxel.h"
#include "..\..\DataCenter\Objects\point.h"
#include "..\..\Utilities\matrix.h"

VoxelGenerator::VoxelGenerator() {
    this->origin = new Point();
    this->direction = new Point();
    this->currPoint = new Point();
    this->tDelta = new Point();
    this->tMax = new Point();
}

VoxelGenerator::~VoxelGenerator() {
    delete this->origin;
    delete this->direction;
    delete this->currPoint;
    delete this->tDelta;
    delete this->tMax;
}

void VoxelGenerator::SeedMesh(Mesh* mesh) {
    delete this->mesh;
    this->mesh = mesh;
}

void VoxelGenerator::SeedRays(Point* origin, Point* direction) {
    double* inverseValues = mesh->GetInverseMatrix()->GetValues();
    double temp[2][3];
    Point* points[2] = {origin, direction};
    for(int i = 0; i < 2; i++) {
        temp[i][0] = (inverseValues[0] * points[i]->GetX()) + (inverseValues[1] * points[i]->GetY()) + (inverseValues[2] * points[i]->GetZ());
        temp[i][1] = (inverseValues[4] * points[i]->GetX()) + (inverseValues[5] * points[i]->GetY()) + (inverseValues[6] * points[i]->GetZ());
        temp[i][2] = (inverseValues[8] * points[i]->GetX()) + (inverseValues[9] * points[i]->GetY()) + (inverseValues[10] * points[i]->GetZ());
    }

    temp[0][0] += (inverseValues[3]);
    temp[0][1] += (inverseValues[7]);
    temp[0][2] += (inverseValues[11]);
    this->origin->ReplaceValues(temp[0]);
    this->direction->ReplaceValues(temp[1]);

    this->direction->Normalize();// reduced fp error; unnecessary tho

    this->stepX = (this->direction->GetX() > 0) ? 1.0 : -1.0;
    this->stepY = (this->direction->GetY() > 0) ? 1.0 : -1.0;
    this->stepZ = (this->direction->GetZ() > 0) ? 1.0 : -1.0;

    this->tDelta->ReplaceValues(
        (this->direction->GetX() != 0) ? std::fabs(1.0 / this->direction->GetX()) : 1e30,
        (this->direction->GetY() != 0) ? std::fabs(1.0 / this->direction->GetY()) : 1e30,
        (this->direction->GetZ() != 0) ? std::fabs(1.0 / this->direction->GetZ()) : 1e30        
    );
}

void VoxelGenerator::PopulateTMax() {
    double ox = this->currPoint->GetX() + (this->direction->GetX() * DBL_EPSILON);
    double oy = this->currPoint->GetY() + (this->direction->GetY() * DBL_EPSILON);
    double oz = this->currPoint->GetZ() + (this->direction->GetZ() * DBL_EPSILON);

    if (this->stepX > 0) {
        this->tMax->SetX((std::floor(ox) + 1.0 - ox) * this->tDelta->GetX());
    } else {
        this->tMax->SetX((ox - std::floor(ox)) * this->tDelta->GetX());
    }

    if (this->stepY > 0) {
        this->tMax->SetY((std::floor(oy) + 1.0 - oy) * this->tDelta->GetY());
    } else {
        this->tMax->SetY((oy - std::floor(oy)) * this->tDelta->GetY());
    }

    if (this->stepZ > 0) {
        this->tMax->SetZ((std::floor(oz) + 1.0 - oz) * this->tDelta->GetZ());
    } else {
        this->tMax->SetZ((oz - std::floor(oz)) * this->tDelta->GetZ());
    }
}

Voxel* VoxelGenerator::FindFirstVoxel() {
    double ox = this->origin->GetX();
    double oy = this->origin->GetY();
    double oz = this->origin->GetZ();

    //check inside volume
    if((ox >= 0) &&
       (oy >= 0) &&
       (oz >= 0) &&
       (ox <= (POINT_CLOUD_WIDTH - 1)) &&
       (oy <= (POINT_CLOUD_HEIGHT - 1)) &&
       (oz <= (POINT_CLOUD_DEPTH - 1))) {

        this->currPoint->ReplaceValues(this->origin);
        this->PopulateTMax();

        this->xIndex = (int)std::floor(ox);
        this->yIndex = (int)std::floor(oy);
        this->zIndex = (int)std::floor(oz);

        this->xIndex = std::max(0, std::min(this->xIndex, POINT_CLOUD_WIDTH));
        this->yIndex = std::max(0, std::min(this->yIndex, POINT_CLOUD_HEIGHT));
        this->zIndex = std::max(0, std::min(this->zIndex, POINT_CLOUD_DEPTH));

        return this->mesh->GetVoxel(this->xIndex, this->yIndex, this->zIndex);
    }

    // might be a small amount of redundancy (we checked already if inside) but acceptable
    double inv = 1.0 / this->direction->GetX();
    double t1 = -ox * inv;
    double t2 = (POINT_CLOUD_WIDTH - 1 - ox) * inv;
    double tnear = std::min(t1, t2);
    double tfar = std::max(t1, t2);

    inv = 1.0 / this->direction->GetY();
    t1 = -oy * inv;
    t2 = (POINT_CLOUD_HEIGHT - 1 - oy) * inv;
    tnear = std::max(tnear, std::min(t1, t2));
    tfar = std::min(tfar, std::max(t1, t2));

    if((tnear > tfar) || (tfar < 0)) {
        return nullptr;
    }

    inv = 1.0 / this->direction->GetZ();
    t1 = -oz * inv;
    t2 = (POINT_CLOUD_DEPTH - 1 - oz) * inv;
    tnear = std::max(tnear, std::min(t1, t2));
    tfar = std::min(tfar, std::max(t1, t2));

    if((tnear > tfar) || (tfar < 0)) {
        return nullptr;
    }

    this->currPoint->ReplaceValues(
        ox + (tnear * this->direction->GetX()),
        oy + (tnear * this->direction->GetY()),
        oz + (tnear * this->direction->GetZ())
    );

    this->PopulateTMax();

    this->xIndex = (int)std::floor(this->currPoint->GetX());
    this->yIndex = (int)std::floor(this->currPoint->GetY());
    this->zIndex = (int)std::floor(this->currPoint->GetZ());

    this->xIndex = std::max(0, std::min(this->xIndex, POINT_CLOUD_WIDTH - 2));
    this->yIndex = std::max(0, std::min(this->yIndex, POINT_CLOUD_HEIGHT - 2));
    this->zIndex = std::max(0, std::min(this->zIndex, POINT_CLOUD_DEPTH - 2));

    return this->mesh->GetVoxel(xIndex, yIndex, zIndex);
}

Voxel* VoxelGenerator::FindNextVoxel() {
    if (this->tMax->GetX() < this->tMax->GetY()) {
        if (this->tMax->GetX() < this->tMax->GetZ()) {
            xIndex += this->stepX;
            this->tMax->ChangeX(this->tDelta->GetX());
        } else {
            zIndex += this->stepZ;
            this->tMax->ChangeZ(this->tDelta->GetZ());
        }
    } else {
        if (this->tMax->GetY() < this->tMax->GetZ()) {
            yIndex += this->stepY;
            this->tMax->ChangeY(this->tDelta->GetY());
        } else {
            zIndex += this->stepZ;
            this->tMax->ChangeZ(this->tDelta->GetZ());
        }
    }

    if((xIndex < 0) ||
       (yIndex < 0) ||
       (zIndex < 0) ||
       (xIndex > (POINT_CLOUD_WIDTH - 2)) ||
       (yIndex > (POINT_CLOUD_HEIGHT - 2)) ||
       (zIndex > (POINT_CLOUD_DEPTH - 2))) {

        return nullptr;
    }

    return this->mesh->GetVoxel(this->xIndex, this->yIndex, this->zIndex);
}
