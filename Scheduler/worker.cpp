#include <iostream>
#include <chrono>
#include <thread>
#include <cfloat>
#include <random>
#include <algorithm>

#include "worker.h"
#include "threadBuffer.h"
#include "..\config.h"

unsigned char act(float value, float i, float n, float amp);

void Worker::ComputePixels(ThreadBuffer* buffer) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::normal_distribution<float> randomColor(-1, 1);

    for(int i = 0; i < buffer->n; i++) {

        // buffer->data[buffer->writeIndex] = act(randomColor(gen), (float)i, (float)buffer->n, 0);
        // buffer->data[buffer->writeIndex + 1] = act(randomColor(gen), (float)i, (float)buffer->n, 50);
        // buffer->data[buffer->writeIndex + 2] = act(randomColor(gen), (float)i, (float)buffer->n, 50);

        buffer->data[buffer->writeIndex] = 40;
        buffer->data[buffer->writeIndex + 1] = 255;
        buffer->data[buffer->writeIndex + 2] = 40;

        Worker::SignalReady(buffer);
    }

    buffer->finished = true;
}

unsigned char act(float value, float i, float n, float amp) {
    return (unsigned char)std::min(std::max((int)(255 * (i / n) + (value * amp)), 0), 255);
}

// Order of expressions is important
void Worker::SignalReady(ThreadBuffer* buffer) {
    buffer->readiness[buffer->writeIndex + 2] = true;
    buffer->readiness[buffer->writeIndex + 1] = true;
    buffer->writeIndex += 3;

    buffer->readiness[buffer->writeIndex - 3] = true;
}