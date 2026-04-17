#ifndef UTILITIES_MATH_UTILITIES_H_
#define UTILITIES_MATH_UTILITIES_H_

#include "matrix.h"
#include "..\DataCenter\Objects\point.h"
#include "..\config.h"

class MathUtilities {
public:
    static void Normalize(double& dx, double& dy, double& dz);
    
    static void RotateCoordinate(RotationType type, double& px, double& py, double& pz, double cosTheta, double sinTheta);
    static unsigned char ColorAmp(double percent);
   
    static void MatrixMultiply(double* multiplier, double* original, double* result);

    static Point CrossProduct(Point* a, Point* b);
    static double DotProduct(Point* a, Point* b);
private:
    MathUtilities() = default;
};

#endif