#ifndef DATA_CENTER_DATA_GENERATOR_H_
#define DATA_CENTER_DATA_GENERATOR_H_

#include "Objects\pointCloud.h"
#include "..\Resources\FastNoiseLite.h"

class DataGenerator {
private:
    FastNoiseLite noiseGenerator;
public:
    DataGenerator();
    ~DataGenerator();

    PointCloud* CreatePointCloud();
};

#endif