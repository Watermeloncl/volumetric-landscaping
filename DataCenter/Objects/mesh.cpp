#include <iostream>
#include <cmath>

#include "mesh.h"
#include "voxel.h"
#include "triangle.h"
#include "pointCloud.h"
#include "..\..\Utilities\matrix.h"
#include "..\..\config.h"

Mesh::Mesh() {
    this->faces[0] = new Face(FaceType::TOP);
    this->faces[1] = new Face(FaceType::BOTTOM);
    this->faces[2] = new Face(FaceType::LEFT);
    this->faces[3] = new Face(FaceType::RIGHT);
    this->faces[4] = new Face(FaceType::FRONT);
    this->faces[5] = new Face(FaceType::BACK);

    this->voxels.resize(POINT_CLOUD_WIDTH - 1, std::vector<std::vector<Voxel*>>(POINT_CLOUD_HEIGHT - 1, std::vector<Voxel*>(POINT_CLOUD_DEPTH - 1, nullptr)));

    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                this->voxels[x][y][z] = new Voxel();
            }
        }
    }

    this->transformMatrix = new Matrix();
}

Mesh::~Mesh() {
    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                delete this->voxels[x][y][z];
            }
        }
    }

    for(int i = 0; i < 6; i++) {
        delete this->faces[i];
    }

    delete this->transformMatrix;
    delete this->inverseMatrix;
}

void Mesh::SetVoxel(int x, int y, int z, Voxel* newVoxel) {
    this->voxels[x][y][z] = newVoxel;
}

Voxel* Mesh::GetVoxel(int x, int y, int z) {
    return this->voxels[x][y][z];
}

void Mesh::AddTriangle(int x, int y, int z, Triangle* newTriangle) {
    this->voxels[x][y][z]->AddTriangle(newTriangle);
}

void Mesh::IncrementTriangleCount() {
    (this->triangleCount)++;
}

int Mesh::GetTriangleCount() {
    return this->triangleCount;
}

Matrix* Mesh::GetTransformMatrix() {
    return this->transformMatrix;
}

Matrix* Mesh::GetInverseMatrix() {
    return this->inverseMatrix;
}

void Mesh::Translate(double transX, double transY, double transZ) {
    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                this->voxels[x][y][z]->Translate(transX, transY, transZ);
            }
        }
    }

    for(Face* face : faces) {
        face->Translate(transX, transY, transZ);
    }

    this->transformMatrix->Translate(transX, transY, transZ);
    this->UpdateInverseMatrix();
}

void Mesh::Rotate(RotationType type, double theta) {
    double cosTheta = std::cos(theta);
    double sinTheta = std::sin(theta);

    for(int x = 0; x < POINT_CLOUD_WIDTH - 1; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT - 1; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH - 1; z++) {
                this->voxels[x][y][z]->Rotate(type, cosTheta, sinTheta);
            }
        }
    }

    for(Face* face : faces) {
        face->Rotate(type, cosTheta, sinTheta);
    }

    this->transformMatrix->Rotate(type, cosTheta, sinTheta);
    this->UpdateInverseMatrix();
}

void Mesh::UpdateInverseMatrix() {
    delete this->inverseMatrix;
    this->inverseMatrix = new Matrix();

    double* baseValues = this->transformMatrix->GetValues();

    // rotation part of matrix
    double rotationTranspose[9] = {
        baseValues[0], baseValues[4], baseValues[8],
        baseValues[1], baseValues[5], baseValues[9],
        baseValues[2], baseValues[6], baseValues[10]
    };

    // translation part of matrix is negated (during multiplication, but it's easier here)
    double translationValues[3] = {
        -baseValues[3],
        -baseValues[7],
        -baseValues[11]
    };

    // calculate R transpose multiplied by -T (negative handled earlier ^^^)
    double result[3];
    double sum;
    for(int i = 0; i < 3; i++) {
        sum = 0;
        for(int j = 0; j < 3; j++) {
            sum += rotationTranspose[i * 3 + j] * translationValues[j];
        }
        result[i] = sum;
    }

    // direct end values
    double finalValues[16] = {
        rotationTranspose[0], rotationTranspose[1], rotationTranspose[2], result[0],
        rotationTranspose[3], rotationTranspose[4], rotationTranspose[5], result[1],
        rotationTranspose[6], rotationTranspose[7], rotationTranspose[8], result[2],
        0, 0, 0, 1
    };

    this->inverseMatrix->FillValues(finalValues);

    std::cout << "inverse matrix:" << std::endl;
    double* invv = this->inverseMatrix->GetValues();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << invv[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
}
