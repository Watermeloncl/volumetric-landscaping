#ifndef CONFIG_H_
#define CONFIG_H_

const int CLIENT_SCREEN_WIDTH = 1280;
const int CLIENT_SCREEN_HEIGHT = 720;

const int NUM_WORKER_THREADS = 10;

const int POINT_CLOUD_WIDTH = 128;
const int POINT_CLOUD_HEIGHT = 32;
const int POINT_CLOUD_DEPTH = 128;

const float PERLIN_HILL_SCALE = 0.08f;
const float ISO_VALUE = -0.3f;

const double MESH_ROTATION = 0.5;
const double MESH_TRANSLATION = -20;

enum class RotationType {
    X,
    Y,
    Z,
};

#endif