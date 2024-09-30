#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class Material;

class HitRecord {
  public:
    point3 p;
    Vector3 normal;
    double t;

    bool front_face;

    void set_face_normal(const Ray& r, const Vector3& outward_normal) {
        front_face = scalarProduct(r.getDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

#endif