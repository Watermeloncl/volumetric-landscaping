#ifndef DATA_CENTER_H_
#define DATA_CENTER_H_

#include "dataGenerator.h"
#include "meshGenerator.h"
#include "parser.h"
#include "Objects\mesh.h"
#include "Objects\worldData.h"
#include "..\RenderFunctions\Objects\lights.h"
#include "..\RenderFunctions\Objects\texture.h"

class DataCenter {
private:
    DataGenerator* dataGenerator = nullptr;
    MeshGenerator* meshGenerator = nullptr;
    Parser* parser = nullptr;

    WorldData* worldData = nullptr;
public:
    DataCenter(char* cmdArgs);
    ~DataCenter();

    Mesh* CreateMesh();
    Lights* CreateLights();
    Texture** CreateTextures();
    WorldData* GetWorldData();

};

#endif