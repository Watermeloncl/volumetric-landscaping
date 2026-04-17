#include <atomic>

#include "threadBuffer.h"
#include "..\DataCenter\Objects\mesh.h"
#include "..\DataCenter\Objects\worldData.h"
#include "..\RenderFunctions\Objects\lights.h"
#include "..\RenderFunctions\Objects\texture.h"

ThreadBuffer::ThreadBuffer(int startX, int startY, int n, Mesh* mesh, Lights* lights, Texture** textures, WorldData* worldData) {
    this->startX = startX;
    this->startY = startY;
    this->n = n;
    this->mesh = mesh;
    this->lights = lights;
    this->textures = textures;
    this->worldData = worldData;

    this->data = new unsigned char[n * 3];
    this->readiness = new std::atomic<bool>[n * 3];
    for(int i = 0; i < (n * 3); i++) {
        this->readiness[i] = false;
    }
}

ThreadBuffer::~ThreadBuffer() {
    delete[] this->data;
    delete[] this->readiness;
}
