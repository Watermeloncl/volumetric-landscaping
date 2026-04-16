#ifndef RENDER_FUNCTIONS_OBJECTS_COLOR_H_
#define RENDER_FUNCTIONS_OBJECTS_COLOR_H_

class Color {
private:
    double red;
    double green;
    double blue;

public:
    Color();
    Color(double red, double green, double blue);
    ~Color();

    void SetRed(double newRed);
    double GetRed();

    void SetGreen(double newGreen);
    double GetGreen();
    
    void SetBlue(double newBlue);
    double GetBlue();
};

#endif