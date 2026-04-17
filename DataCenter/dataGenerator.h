#ifndef DATA_CENTER_DATA_GENERATOR_H_
#define DATA_CENTER_DATA_GENERATOR_H_

#include "Objects\pointCloud.h"
#include "Objects\worldData.h"
#include "..\Resources\FastNoiseLite.h"

class DataGenerator {
private:
    FastNoiseLite noiseGenerator;
public:
    DataGenerator(WorldData* WorldData);
    ~DataGenerator();

    PointCloud* CreatePointCloud();
};

#endif