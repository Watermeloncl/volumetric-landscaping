#include <windows.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

#include "scheduler.h"
#include "..\Display\display.h"
#include "threadBuffer.h"
#include "worker.h"
#include "..\config.h"

using SchedClock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;
using TimeStamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

SchedulerModule::SchedulerModule(HINSTANCE hInstance, int nCmdShow) {
    this->display = new DisplayModule(hInstance, nCmdShow);
}

SchedulerModule::~SchedulerModule() {
    delete this->display;
    for(int i = 0; i < NUM_WORKER_THREADS; i++) {
        delete this->buffers[i];
    }
    delete[] this->buffers;

    for(std::thread &t : workers) {
        if(t.joinable()) {
            t.join();
        }
    }
}

void SchedulerModule::RunMainLoop() {
    this->InitThreads();

    TimeStamp lastTime = SchedClock::now();
    TimeStamp now = SchedClock::now();

    Duration elapsed;
    double accumulator = 0.0;
    const double dt = 1.0 / 60.0;

    int frame = 0;
    bool running = true;

    MSG msg = {};
    while(running) {
        while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        now = SchedClock::now();
        elapsed = now - lastTime;
        lastTime = now;
        accumulator += elapsed.count();
 
        while(accumulator >= dt) {
            frame++;

            for(int i = 0; i < NUM_WORKER_THREADS; i++) {
                this->AddPixels(this->buffers[i], i);
            }

            accumulator -= dt;
        }

        this->display->RenderFrame();
    }
}

void SchedulerModule::InitThreads() {
    this->buffers = new ThreadBuffer*[NUM_WORKER_THREADS];

    int totalPixels = CLIENT_SCREEN_WIDTH * CLIENT_SCREEN_HEIGHT;
    int n = totalPixels / NUM_WORKER_THREADS;
    int startY;

    for(int i = 0; i < NUM_WORKER_THREADS; i++) {
        startY = (n * i) / CLIENT_SCREEN_WIDTH;
        ThreadBuffer* buffer = new ThreadBuffer(0, startY, n);
        this->buffers[i] = buffer;

        this->workers.push_back(std::thread(Worker::ComputePixels, buffer));
    }
}

void SchedulerModule::AddPixels(ThreadBuffer* buffer, int threadNum) {
    int destinationIndex = buffer->startY * CLIENT_SCREEN_WIDTH;
    int dest3Index = destinationIndex * 3;
    int sourceIndex = buffer->readIndex + 1;

    while(buffer->readiness[sourceIndex]) {
        this->display->GetScreen()->AddPixel(destinationIndex, 0xFF000000 | (((UINT32)(buffer->data[sourceIndex])) << 16) | (((UINT32)(buffer->data[sourceIndex + 1])) << 8) | ((UINT32)(buffer->data[sourceIndex + 2])));

        destinationIndex++;
        sourceIndex += 3;
        dest3Index += 3;
    }
}