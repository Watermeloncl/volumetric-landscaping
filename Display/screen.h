#ifndef DISPLAY_SCREEN_H_
#define DISPLAY_SCREEN_H_

#include <windows.h>

class Screen {
private:
    UINT32* pixels = nullptr;

public:
    Screen();
    ~Screen();

    UINT32* GetPixels();
    void AddPixel(int index, UINT32 color);
};

#endif