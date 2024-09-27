#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord {
  public:
    point3 p;
    Vector3 normal;
    double t;
};

class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

#endif