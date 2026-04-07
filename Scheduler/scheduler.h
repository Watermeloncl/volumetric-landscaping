#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <windows.h>

#include "..\Display\display.h"

class SchedulerModule {
public:
private:
    DisplayModule* display = NULL;
public:
    SchedulerModule(HINSTANCE hInstance, int nCmdShow);
    ~SchedulerModule();

    void RunMainLoop();
private:
};

#endif