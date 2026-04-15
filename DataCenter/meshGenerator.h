#ifndef DATA_CENTER_MESH_GENERATOR_H_
#define DATA_CENTER_MESH_GENERATOR_H_

#include "Objects\mesh.h"
#include "Objects\pointCloud.h"

class MeshGenerator {
private:
    static int triTable[256][16];
    static int edgeTable[256];

public:
    MeshGenerator();
    ~MeshGenerator();

    Mesh* CreateMesh(PointCloud* pointCloud);
    double InterpolateVertex(float density1, float density2);

    void TransformMesh(Mesh* mesh);
};

#endif