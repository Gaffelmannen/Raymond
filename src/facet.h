#ifndef FACET_H
#define FACET_H

#include "Ray.h"

struct recordHit
{
      point3 p;
      Vector3 normal;
      double t;
};

class Facet
{
  public:
      virtual bool hit(
        const Ray& ray,
        double t_min,
        double t_max,
        recordHit& rec
      ) const = 0;
};

#endif
