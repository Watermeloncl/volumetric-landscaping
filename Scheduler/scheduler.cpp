#include <windows.h>
#include <iostream>
#include <chrono>

#include "scheduler.h"
#include "..\Display\display.h"
#include "..\config.h"

using SchedClock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;
using TimeStamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

SchedulerModule::SchedulerModule(HINSTANCE hInstance, int nCmdShow) {
    this->display = new DisplayModule(hInstance, nCmdShow);
}

SchedulerModule::~SchedulerModule() {
    delete this->display;
}

void SchedulerModule::RunMainLoop() {
    TimeStamp lastTime = SchedClock::now();
    TimeStamp now = SchedClock::now();

    Duration elapsed;
    double accumulator = 0.0;
    const double dt = 1.0 / 60.0;

    int frame = 0;
    bool running = true;

    unsigned char r, g, b;

    UINT32* g_pixels = new UINT32[CLIENT_SCREEN_WIDTH * CLIENT_SCREEN_HEIGHT];
    for(int y = 0; y < CLIENT_SCREEN_HEIGHT; y++) {
        for (int x = 0; x < CLIENT_SCREEN_WIDTH; x++) {
            g_pixels[y * CLIENT_SCREEN_WIDTH + x] = 0xFF000000;
        }
    }

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

            for(int y = 0; y < CLIENT_SCREEN_HEIGHT; y++) {
                for (int x = 0; x < CLIENT_SCREEN_WIDTH; x++) {
                    r = (unsigned char)((x + frame) % 256);
                    g = (unsigned char)((y + frame) % 256);
                    b = (unsigned char)((x + y + frame) % 256);
                    g_pixels[y * CLIENT_SCREEN_WIDTH + x] = 0xFF000000 | (((UINT32)r) << 16) | (((UINT32)g) << 8) | ((UINT32)b);
                }
            }

            accumulator -= dt;
        }

        this->display->RenderFrame(g_pixels);
    }


}