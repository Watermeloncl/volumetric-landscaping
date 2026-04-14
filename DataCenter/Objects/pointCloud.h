#ifndef DATA_CENTER_POINT_CLOUD_H_
#define DATA_CENTER_POINT_CLOUD_H_

#include <vector>

class PointCloud {
private:
    std::vector<std::vector<std::vector<float>>> densityCloud;

public:
    PointCloud();
    ~PointCloud();

    void SetValue(int x, int y, int z, float v);
    float GetValue(int x, int y, int z);
};

#endif