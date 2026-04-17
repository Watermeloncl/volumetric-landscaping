#ifndef CONFIG_H_
#define CONFIG_H_

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

/* parser values? */

const bool RANDOM_SEED = false;
const float PERLIN_HILL_SCALE = 0.015f;
const int FRACTAL_OCTAVES = 6;
const float FRACTAL_LACUNARITY = 2.0f;
const float FRACTAL_GAIN = 0.5f;

const float ISO_VALUE = -0.3f;//-0.3f;

const double MESH_ROTATION = -0.4; //-0.5
const double MESH_Y_TRANSLATION = 0;
const double MESH_Z_TRANSLATION = 60;

const double VIEW_DISTANCE = 800; //100
const double WORLD_WINDOW_SIZE = 11.0; // What's a good value here?

const double Ka = 0.1;
const double Kd = 0.89;
const double Ks = 0.01;
const double Kgls = 4.0;

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