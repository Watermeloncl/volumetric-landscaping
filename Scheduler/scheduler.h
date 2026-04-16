#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <windows.h>
#include <vector>
#include <thread>

#include "..\Display\display.h"
#include "..\Scheduler\threadBuffer.h"
#include "..\DataCenter\dataCenter.h"
#include "..\DataCenter\Objects\mesh.h"

class SchedulerModule {
public:
private:
    DisplayModule* display = nullptr;

    std::vector<std::thread> workers;
    ThreadBuffer** buffers = nullptr;

    DataCenter* dataCenter = nullptr;

    Mesh* mesh = nullptr;
public:
    SchedulerModule(HINSTANCE hInstance, int nCmdShow);
    ~SchedulerModule();

    void RunMainLoop();
    void InitThreads(Mesh* mesh);
    void AddPixels(ThreadBuffer* buffer, int threadNum);

private:

};

#endif