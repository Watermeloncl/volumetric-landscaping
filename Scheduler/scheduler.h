#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <windows.h>
#include <vector>
#include <thread>

#include "..\Display\display.h"
#include "..\Scheduler\threadBuffer.h"
#include "..\DataCenter\dataCenter.h"
#include "..\DataCenter\Objects\mesh.h"
#include "..\RenderFunctions\Objects\lights.h"

class SchedulerModule {
public:
private:
    DisplayModule* display = nullptr;

    std::vector<std::thread> workers;
    ThreadBuffer** buffers = nullptr;

    DataCenter* dataCenter = nullptr;

    Mesh* mesh = nullptr;
    Lights* lights = nullptr;
public:
    SchedulerModule(HINSTANCE hInstance, int nCmdShow);
    ~SchedulerModule();

    void RunMainLoop();
    void InitThreads();
    void AddPixels(ThreadBuffer* buffer, int threadNum);

private:

};

#endif