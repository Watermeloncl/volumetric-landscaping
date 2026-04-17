#include <iostream>
#include <chrono>
#include <thread>
#include <cfloat>
#include <random>
#include <algorithm>

#include "worker.h"
#include "threadBuffer.h"
#include "..\DataCenter\Objects\mesh.h"
#include "..\RenderFunctions\renderFunctions.h"
#include "..\RenderFunctions\Objects\collisionPacket.h"
#include "..\RenderFunctions\Objects\color.h"
#include "..\RenderFunctions\Objects\lights.h"
#include "..\RenderFunctions\Objects\voxelGenerator.h"
#include "..\Utilities\mathUtilities.h"
#include "..\config.h"

void Worker::ComputePixels(ThreadBuffer* buffer) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::normal_distribution<float> randomColor(-1, 1);

    Mesh* mesh = buffer->mesh;
    Lights* lights = buffer->lights;
    VoxelGenerator* generator = new VoxelGenerator();

    Point* origin = new Point(0, 0, -VIEW_DISTANCE);
    Point* direction = new Point(0, 0, VIEW_DISTANCE);

    double leftX = (WORLD_WINDOW_SIZE * CLIENT_SCREEN_RATIO_WIDTH) / -2.0;
    double rightX = (WORLD_WINDOW_SIZE * CLIENT_SCREEN_RATIO_WIDTH) / 2.0;
    double upY = (WORLD_WINDOW_SIZE * CLIENT_SCREEN_RATIO_HEIGHT) / 2.0;

    double pixelSize = (WORLD_WINDOW_SIZE * CLIENT_SCREEN_RATIO_WIDTH) / CLIENT_SCREEN_WIDTH;
    double halfPixelSize = pixelSize / 2.0;

    double currX = (buffer->startX * pixelSize) + leftX + halfPixelSize;
    double currY = upY - (buffer->startY * pixelSize) - halfPixelSize;

    generator->SeedMesh(mesh);

    for(int i = 0; i < buffer->n; i++) {
        direction->ReplaceValues(currX, currY, VIEW_DISTANCE);
        direction->Normalize();

        generator->SeedRays(origin, direction);
        CollisionPacket* collisionPacket = RenderFunctions::FindCollision(origin, direction, generator);
        Color* color = RenderFunctions::CalcColor(collisionPacket, direction, lights);

        buffer->data[buffer->writeIndex] = MathUtilities::ColorAmp(color->GetRed());
        buffer->data[buffer->writeIndex + 1] = MathUtilities::ColorAmp(color->GetGreen());
        buffer->data[buffer->writeIndex + 2] = MathUtilities::ColorAmp(color->GetBlue());

        delete collisionPacket;
        delete color;

        Worker::SignalReady(buffer);

        currX += pixelSize;
        if(currX > rightX) {
            currX = leftX + halfPixelSize;
            currY -= pixelSize;
        }
    }

    buffer->finished = true;
}

// Order of expressions is important
void Worker::SignalReady(ThreadBuffer* buffer) {
    buffer->readiness[buffer->writeIndex + 2] = true;
    buffer->readiness[buffer->writeIndex + 1] = true;
    buffer->writeIndex += 3;

    buffer->readiness[buffer->writeIndex - 3] = true;
}