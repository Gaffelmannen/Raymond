#ifndef SPHERE_H
#define SPHERE_H

#include "facet.h"
#include "Vector3.h"

class Sphere
{
public:
  Sphere() {}
  Sphere(point3 center, double r) : center(cen), radius(r) {};

  virtual bool hit(
    const Ray& r, double tmin, double tmax, recordHit& rec
  ) const override;
};

#endif
