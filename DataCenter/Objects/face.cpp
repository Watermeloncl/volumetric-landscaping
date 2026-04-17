#include "face.h"
#include "..\..\config.h"

Face::Face(FaceType type) {
    switch(type) {
        case FaceType::TOP:
            corners[0] = new Point(0, POINT_CLOUD_HEIGHT, 0);
            corners[1] = new Point(0, POINT_CLOUD_HEIGHT, POINT_CLOUD_DEPTH);
            corners[2] = new Point(POINT_CLOUD_WIDTH, POINT_CLOUD_HEIGHT, POINT_CLOUD_DEPTH);
            corners[3] = new Point(POINT_CLOUD_WIDTH, POINT_CLOUD_HEIGHT, 0);

            normal = new Point(0, 1, 0);
            break;
        case FaceType::BOTTOM:
            corners[0] = new Point(0, 0, 0);
            corners[1] = new Point(POINT_CLOUD_WIDTH, 0, 0);
            corners[2] = new Point(POINT_CLOUD_WIDTH, 0, POINT_CLOUD_DEPTH);
            corners[3] = new Point(0, 0, POINT_CLOUD_DEPTH);

            normal = new Point(0, -1, 0);
            break;
        case FaceType::LEFT:
            corners[0] = new Point(0, 0, 0);
            corners[1] = new Point(0, 0, POINT_CLOUD_DEPTH);
            corners[2] = new Point(0, POINT_CLOUD_HEIGHT, POINT_CLOUD_DEPTH);
            corners[3] = new Point(0, POINT_CLOUD_HEIGHT, 0);

            normal = new Point(-1, 0, 0);
            break;
        case FaceType::RIGHT:
            corners[0] = new Point(POINT_CLOUD_WIDTH, 0, 0);
            corners[1] = new Point(POINT_CLOUD_WIDTH, POINT_CLOUD_HEIGHT, 0);
            corners[2] = new Point(POINT_CLOUD_WIDTH, POINT_CLOUD_HEIGHT, POINT_CLOUD_DEPTH);
            corners[3] = new Point(POINT_CLOUD_WIDTH, 0, POINT_CLOUD_DEPTH);

            normal = new Point(1, 0, 0);
            break;
        case FaceType::FRONT:
            corners[0] = new Point(0, 0, 0);
            corners[1] = new Point(0, POINT_CLOUD_HEIGHT, 0);
            corners[2] = new Point(POINT_CLOUD_WIDTH, POINT_CLOUD_HEIGHT, 0);
            corners[3] = new Point(POINT_CLOUD_WIDTH, 0, 0);

            normal = new Point(0, 0, -1);
            break;
        case FaceType::BACK:
            corners[0] = new Point(0, 0, POINT_CLOUD_DEPTH);
            corners[1] = new Point(POINT_CLOUD_WIDTH, 0, POINT_CLOUD_DEPTH);
            corners[2] = new Point(POINT_CLOUD_WIDTH, POINT_CLOUD_HEIGHT, POINT_CLOUD_DEPTH);
            corners[3] = new Point(0, POINT_CLOUD_HEIGHT, POINT_CLOUD_DEPTH);

            normal = new Point(0, 0, 1);
            break;
    }
}

Face::~Face() {
    for(int i = 0; i < 4; i++) {
        delete this->corners[i];
    }

    delete this->normal;
}

void Face::Translate(double transX, double transY, double transZ) {
    for(Point* point : this->corners) {
        point->ChangeX(transX);
        point->ChangeY(transY);
        point->ChangeZ(transZ);
    }
}

void Face::Rotate(RotationType type, double cosTheta, double sinTheta) {
    for(Point* point : this->corners) {
        point->Rotate(type, cosTheta, sinTheta);
    }

    normal->Rotate(type, cosTheta, sinTheta);
    normal->Normalize(); //precaution
}