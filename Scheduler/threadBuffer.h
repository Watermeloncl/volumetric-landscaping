#ifndef SCHEDULER_THREAD_BUFFER_H_
#define SCHEDULER_THREAD_BUFFER_H_

#include <atomic>
#include <stack>

#include "..\DataCenter\Objects\mesh.h"

struct ThreadBuffer {
public:
    std::atomic<int> readIndex = -1;
    std::atomic<int> writeIndex = 0;
    std::atomic<bool> finished = false;
    unsigned char* volatile data = nullptr;
    std::atomic<bool>* volatile readiness = nullptr;

    int startX = 0;
    int startY = 0;
    int n = 0;
    Mesh* mesh;

    ThreadBuffer(int startX, int startY, int n, Mesh* mesh);
    ~ThreadBuffer();
};

#endif