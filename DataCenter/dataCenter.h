#ifndef DATA_CENTER_H_
#define DATA_CENTER_H_

#include "dataGenerator.h"
#include "meshGenerator.h"
#include "parser.h"
#include "Objects\mesh.h"

class DataCenter {
private:
    DataGenerator* dataGenerator = nullptr;
    MeshGenerator* meshGenerator = nullptr;
    Parser* parser = nullptr;

public:
    DataCenter();
    ~DataCenter();

    Mesh* CreateMesh();
};

#endif