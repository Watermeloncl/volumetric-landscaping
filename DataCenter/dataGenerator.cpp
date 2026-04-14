#include <iostream>

#include "dataGenerator.h"
#include "Objects\pointCloud.h"
#include "..\Resources\FastNoiseLite.h"
#include "..\config.h"

DataGenerator::DataGenerator() {
    this->noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    this->noiseGenerator.SetFrequency(PERLIN_HILL_SCALE);
}

DataGenerator::~DataGenerator() {

}

PointCloud* DataGenerator::CreatePointCloud() {
    PointCloud* cloud = new PointCloud();
 
    float newNoise;
    for(int x = 0; x < POINT_CLOUD_SIZE; x++) {
        for(int y = 0; y < POINT_CLOUD_SIZE; y++) {
            for(int z = 0; z < POINT_CLOUD_SIZE; z++) {
                newNoise = this->noiseGenerator.GetNoise((float)x, (float)y, (float)z);
                newNoise -= ((float)y) / (2.0f * (float)POINT_CLOUD_SIZE);

                cloud->SetValue(x, y, z, newNoise);
            }
        }
    }

    return cloud;
}