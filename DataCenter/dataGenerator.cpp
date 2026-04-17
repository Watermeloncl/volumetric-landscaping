#include <iostream>
#include <ctime>

#include "dataGenerator.h"
#include "Objects\pointCloud.h"
#include "..\Resources\FastNoiseLite.h"
#include "..\config.h"

DataGenerator::DataGenerator() {
    if(RANDOM_SEED) {
        unsigned int seed = static_cast<unsigned int>(std::time(NULL));
        this->noiseGenerator.SetSeed(seed);
    }
    
    this->noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    this->noiseGenerator.SetFrequency(PERLIN_HILL_SCALE);
    this->noiseGenerator.SetFractalOctaves(FRACTAL_OCTAVES);
    this->noiseGenerator.SetFractalLacunarity(FRACTAL_LACUNARITY);
    this->noiseGenerator.SetFractalGain(0.5f);
    this->noiseGenerator.SetFractalType(FastNoiseLite::FractalType_FBm);
}

DataGenerator::~DataGenerator() {

}

PointCloud* DataGenerator::CreatePointCloud() {
    PointCloud* cloud = new PointCloud();
 
    float newNoise;
    for(int x = 0; x < POINT_CLOUD_WIDTH; x++) {
        for(int y = 0; y < POINT_CLOUD_HEIGHT; y++) {
            for(int z = 0; z < POINT_CLOUD_DEPTH; z++) {
                newNoise = this->noiseGenerator.GetNoise((float)x, (float)y, (float)z);
                newNoise -= ((float)y) / (2.0f * (float)POINT_CLOUD_HEIGHT);

                cloud->SetValue(x, y, z, newNoise);
            }
        }
    }

    // std::cout << "temp noise added" << std::endl;
    // float newNoise;
    // for(int x = 0; x < POINT_CLOUD_WIDTH; x++) {
    //     for(int y = 0; y < POINT_CLOUD_HEIGHT; y++) {
    //         for(int z = 0; z < POINT_CLOUD_DEPTH; z++) {
    //             newNoise = (y > 1) ? 0 : 1;
    //             cloud->SetValue(x, y, z, newNoise);
    //         }
    //     }
    // }

    return cloud;
}