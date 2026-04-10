#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <windows.h>
#include <vector>
#include <thread>

#include "..\Display\display.h"
#include "..\Scheduler\threadBuffer.h"

class SchedulerModule {
public:
private:
    DisplayModule* display = nullptr;

    std::vector<std::thread> workers;
    ThreadBuffer** buffers = nullptr;
public:
    SchedulerModule(HINSTANCE hInstance, int nCmdShow);
    ~SchedulerModule();

    void RunMainLoop();
    void InitThreads();
    void AddPixels(ThreadBuffer* buffer, int threadNum);
private:
};

#endif