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

// Clips color from 0 to 1 and multiplies by max_color
unsigned char MathUtilities::ColorAmp(double percent) {
    if(percent > 1) {
        percent = 1;
    } else if(percent < 0) {
        percent = 0;
    }

    return (unsigned char)(percent * MAX_COLOR);
}
