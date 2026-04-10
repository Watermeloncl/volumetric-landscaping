#include <windows.h>

#include "screen.h"
#include "..\config.h"

Screen::Screen() {
    this->pixels = new UINT32[CLIENT_SCREEN_HEIGHT * CLIENT_SCREEN_WIDTH];
    for(int y = 0; y < CLIENT_SCREEN_HEIGHT; y++) {
        for(int x = 0; x < CLIENT_SCREEN_WIDTH; x++) {
            this->pixels[y * CLIENT_SCREEN_WIDTH + x] = 0xFF000000;
        }
    }
}

Screen::~Screen() {

}

UINT32* Screen::GetPixels() {
    return this->pixels;
}

void Screen::AddPixel(int index, UINT32 color) {
    this->pixels[index] = color;
}