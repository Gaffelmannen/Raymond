#include "Ray.h"

Ray::Ray()
{
    
}

Ray::Ray(const point3& p, const Vector3& v)
{
    origin = p;
    direction = v;
}

point3 Ray::getOrigin() const
{
    return Ray::origin;
}

Vector3 Ray::getDirection() const
{
    return Ray::direction;
}

point3 Ray::at(double t) const
{
    return origin + t * direction;
}
