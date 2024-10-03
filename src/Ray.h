#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
    public:
        point3 origin;
        Vector3 direction;
        
        Ray();
        Ray(const point3&, const Vector3&);
        
        point3 getOrigin() const;
        Vector3 getDirection() const;
        
        point3 at(double) const;
};

#endif
