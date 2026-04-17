#ifndef CONFIG_H_
#define CONFIG_H_

const int CLIENT_SCREEN_WIDTH = 1280;
const int CLIENT_SCREEN_HEIGHT = 720;
const int CLIENT_SCREEN_RATIO_WIDTH = 16;
const int CLIENT_SCREEN_RATIO_HEIGHT = 9;

const int NUM_WORKER_THREADS = 1;

const int POINT_CLOUD_WIDTH = 4; //128
const int POINT_CLOUD_HEIGHT = 4; //32
const int POINT_CLOUD_DEPTH = 4; //128

const int MAX_COLOR = 255;

const int MATRIX_SIZE = 16;

const double RAY_EPSILON = 0.000001;

/* parser values? */

const float PERLIN_HILL_SCALE = 0.08f;
const float ISO_VALUE = -0.3f;

const double MESH_ROTATION = -0.9; //-0.5
const double MESH_TRANSLATION = -20;

const double VIEW_DISTANCE = 5; //100
const double WORLD_WINDOW_SIZE = 1.0; // What's a good value here?

/* ^^^^^^^^^^^ */

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