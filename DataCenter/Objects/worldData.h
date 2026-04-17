#ifndef DATA_CENTER_OBJECTS_WORLD_DATA_H_
#define DATA_CENTER_OBJECTS_WORLD_DATA_H_

struct WorldData {
public:
    double ALT_COLOR_R = 0.2196;
    double ALT_COLOR_G = 0.7843;
    double ALT_COLOR_B = 0.3725;

    bool TEXTURES_ON = true;
    bool RANDOM_SEED = false;
    float PERLIN_HILL_SCALE = 0.015f;
    int FRACTAL_OCTAVES = 6;
    float FRACTAL_LACUNARITY = 2.0f;
    float FRACTAL_GAIN = 0.5f;

    float ISO_VALUE = -0.1f;//-0.3f;

    double MESH_ROTATION = -0.4; //-0.5
    double MESH_Y_TRANSLATION = 0;
    double MESH_Z_TRANSLATION = 60;

    double VIEW_DISTANCE = 800; //100
    double WORLD_WINDOW_SIZE = 11.0; // What's a good value here?

    double Ka = 0.1;
    double Kd = 0.89;
    double Ks = 0.01;
    double Kgls = 4.0;

    double SAND_LEVEL = 5.0;
    double GRASS_LEVEL = 0.25;
    double ROCK_LEVEL = -0.15;
};

#endif