#ifndef UTILITIES_MATRIX_H_
#define UTILITIES_MATRIX_H_

#include "..\config.h"

//could be template, but we only use it for doubles...
class Matrix {
private:

    /*
     * Defined as
     *  0 1 2 3
     *  4 5 6 7
     *  8 9 10 11
     *  12 13 14 15
     * 
     * so, values[8] will get 8
    */

    double values[MATRIX_SIZE];
public:
    Matrix();
    ~Matrix();

    void Reset();
    void Translate(double transX, double transY, double transZ);
    void Rotate(RotationType type, double cosTheta, double sinTheta);

    double* GetValues();
    void FillValues(double* values);
};

#endif