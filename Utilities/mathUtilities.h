#ifndef UTILITIES_MATH_UTILITIES_H_
#define UTILITIES_MATH_UTILITIES_H_

#include "..\config.h"

class MathUtilities {
public:
    static void Normalize(double& dx, double& dy, double& dz);
    
    static void RotateCoordinate(RotationType type, double& px, double& py, double& pz, double cosTheta, double sinTheta);
    static unsigned char ColorAmp(double percent);
    
private:
    MathUtilities() = default;
};

#endif