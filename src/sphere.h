#ifndef SPHERE_H
#define SPHERE_H

#include "facet.h"
#include "Vector3.h"
#include "hittable.h"

class Sphere : public Hittable {
  public:
    Sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, recordHit& rec) const override {
        Vector3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = scalarProduct(oc, r.direction());
        auto c = oc.lengthSquared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (-half_b + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        return true;
    }

  private:
    point3 center;
    double radius;
};

#endif


