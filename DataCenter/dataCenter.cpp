#include "dataCenter.h"
#include "Objects\mesh.h"
#include "Objects\pointCloud.h"
#include "Objects\worldData.h"
#include "..\RenderFunctions\Objects\lights.h"
#include "..\RenderFunctions\Objects\texture.h"

DataCenter::DataCenter(char* cmdArgs) {
    this->parser = new Parser();
    this->worldData = this->parser->ParseFile(cmdArgs);
    this->dataGenerator = new DataGenerator(this->worldData);
    this->meshGenerator = new MeshGenerator(this->worldData);
    this->parser = new Parser();
}

DataCenter::~DataCenter() {
    delete this->dataGenerator;
    delete this->parser;
}

Mesh* DataCenter::CreateMesh() {

    //todo do parser stuff

    PointCloud* cloud = this->dataGenerator->CreatePointCloud(/*parser info?*/);
    Mesh* mesh = this->meshGenerator->CreateMesh(cloud);
    delete cloud;

    this->meshGenerator->TransformMesh(mesh/*, parser info*/);

    return mesh;
}

Lights* DataCenter::CreateLights() {
    // temp, until parsed out by parser
    return new Lights(
        new Color(0.2, 0.2, 0.2), //background
        new Color(0.2, 0.2, 0.2), //ambient
        new Color(1.0, 1.0, 1.0), //light color
        new Point(1, 1, -1) // light direction
    );
}

Texture** DataCenter::CreateTextures() {
    Texture** textures = new Texture*[NUM_TEXTURES];
    textures[0] = new Texture("dirt");
    textures[1] = new Texture("grass");
    textures[2] = new Texture("rock");
    textures[3] = new Texture("sand");
    return textures;
}

WorldData* DataCenter::GetWorldData() {
    return this->worldData;
}
