#include <iostream>
#include <cstring>

#include "matrix.h"
#include "mathUtilities.h"
#include "..\config.h"

Matrix::Matrix() {
    this->Reset();
}

Matrix::~Matrix() {

}

void Matrix::Reset() {
    memset(this->values, 0, MATRIX_SIZE * sizeof(double));
    for(int i = 0; i < MATRIX_SIZE; i += 4 + 1) {
        this->values[i] = 1;
    }
}

void Matrix::Translate(double transX, double transY, double transZ) {
    double transMatrix[MATRIX_SIZE] = {
        1, 0, 0, transX,
        0, 1, 0, transY,
        0, 0, 1, transZ,
        0, 0, 0, 1
    };

    double result[MATRIX_SIZE];
    MathUtilities::MatrixMultiply(transMatrix, this->values, result);
    this->FillValues(result);
}

void Matrix::Rotate(RotationType type, double cosTheta, double sinTheta) {
    double rotationMatrix[MATRIX_SIZE] = {0};
    double result[MATRIX_SIZE];

    rotationMatrix[15] = 1;

    switch(type) {
        case RotationType::X:
            rotationMatrix[0] = 1;
            rotationMatrix[5] = cosTheta;
            rotationMatrix[6] = -sinTheta;
            rotationMatrix[9] = sinTheta;
            rotationMatrix[10] = cosTheta;
            break;
        case RotationType::Y:
            rotationMatrix[0] = cosTheta;
            rotationMatrix[2] = sinTheta;
            rotationMatrix[5] = 1;
            rotationMatrix[8] = -sinTheta;
            rotationMatrix[10] = cosTheta;
            break;
        case RotationType::Z:
            rotationMatrix[0] = cosTheta;
            rotationMatrix[1] = -sinTheta;
            rotationMatrix[4] = sinTheta;
            rotationMatrix[5] = cosTheta;
            rotationMatrix[10] = 1;
            break;
    }

    MathUtilities::MatrixMultiply(rotationMatrix, this->values, result);
    this->FillValues(result);
}

double* Matrix::GetValues() {
    return this->values;
}

void Matrix::FillValues(double* values) {
    for(int i = 0; i < 16; i++) {
        this->values[i] = values[i];
    }
}
