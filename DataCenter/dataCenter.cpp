#include "dataCenter.h"
#include "Objects\mesh.h"
#include "Objects\pointCloud.h"
#include "..\RenderFunctions\Objects\lights.h"

DataCenter::DataCenter() {
    this->dataGenerator = new DataGenerator();
    this->meshGenerator = new MeshGenerator();
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
        new Point(-1, -1, 1) // light direction
    );
}
