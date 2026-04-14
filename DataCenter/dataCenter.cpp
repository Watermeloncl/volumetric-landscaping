#include "dataCenter.h"
#include "Objects\mesh.h"
#include "Objects\pointCloud.h"

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

    return mesh;
}