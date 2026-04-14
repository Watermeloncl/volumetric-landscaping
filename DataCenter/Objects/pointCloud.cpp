#include <vector>

#include "pointCloud.h"
#include "..\..\Resources\FastNoiseLite.h"
#include "..\..\config.h"

PointCloud::PointCloud() {
    this->densityCloud.resize(POINT_CLOUD_SIZE, std::vector<std::vector<float>>(POINT_CLOUD_SIZE, std::vector<float>(POINT_CLOUD_SIZE, 0)));
}

PointCloud::~PointCloud() {
    
}

void PointCloud::SetValue(int x, int y, int z, float v) {
    this->densityCloud[x][y][z] = v;
}

float PointCloud::GetValue(int x, int y, int z) {
    return this->densityCloud[x][y][z];
}
