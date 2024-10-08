#ifndef MISC_H
#define MISC_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Misc Functions
inline double degreesToRadians(double degrees) 
{
    return degrees * pi / 180.0;
}

inline double randomDouble() 
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) 
{
    return min + (max-min)*randomDouble();
}

inline double linearToGamma(double linearComponent)
{
    if (linearComponent > 0)
    {
        return std::sqrt(linearComponent);
    }

    return 0;
}

#include "Ray.h"
#include "Vector3.h"

#endif