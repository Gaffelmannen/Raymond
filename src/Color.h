#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <vector>

#include "misc.h"
#include "Vector3.h"

using namespace std;

class Color : Vector3
{
    private:
        double clamp(double) const;

    public:
        vector<int> SetPixelColor(color);
        vector<int> SetPixelColorAntialiasing(color);
};

#endif
