#ifndef CONFIG_H_
#define CONFIG_H_

// non parsed values

const int CLIENT_SCREEN_WIDTH = 1280;
const int CLIENT_SCREEN_HEIGHT = 720;
const int CLIENT_SCREEN_RATIO_WIDTH = 16;
const int CLIENT_SCREEN_RATIO_HEIGHT = 9;

const int NUM_WORKER_THREADS = 10;

const int POINT_CLOUD_WIDTH = 128; //128
const int POINT_CLOUD_HEIGHT = 32; //32
const int POINT_CLOUD_DEPTH = 128; //128

const int MAX_COLOR = 255;

const int MATRIX_SIZE = 16;

const double RAY_EPSILON = 0.000001;

const int NUM_TEXTURES = 4;

enum class RotationType {
    X,
    Y,
    Z,
};

enum class FaceType {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

#endif