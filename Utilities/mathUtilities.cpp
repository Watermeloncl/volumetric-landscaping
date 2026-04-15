#include <cmath>

#include "mathUtilities.h"
#include "..\config.h"

void MathUtilities::Normalize(double& dx, double& dy, double& dz) {
    double mag = 1.0 / std::sqrt(dx*dx + dy*dy + dz*dz);
    dx *= mag;
    dy *= mag;
    dz *= mag;
}

void MathUtilities::RotateCoordinate(RotationType type, double& px, double& py, double& pz, double cosTheta, double sinTheta) {
    double newX, newY, newZ;

    switch(type) {
        case RotationType::X:
            newY = (cosTheta * py) - (sinTheta * pz);
            newZ = (sinTheta * py) + (cosTheta * pz);
            py = newY;
            pz = newZ;
            break;
        case RotationType::Y:
            newX = (cosTheta * px) + (sinTheta * pz);
            newZ = (-sinTheta * px) + (cosTheta * pz);
            px = newX;
            pz = newZ;
            break;
        case RotationType::Z:
            newX = (cosTheta * px) - (sinTheta * py);
            newY = (sinTheta * px) + (cosTheta * py);
            px = newX;
            py = newY;
            break;
    }
}

