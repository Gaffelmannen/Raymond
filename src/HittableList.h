#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public Hittable {
  public:
    std::vector<shared_ptr<Hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override 
    {
        HitRecord temp_rec;
        bool hitAnything = false;
        auto closestSoFar = ray_tmax;

        for (const auto& object : objects) 
        {
            if (object->hit(r, ray_tmin, closestSoFar, temp_rec)) 
            {
                hitAnything = true;
                closestSoFar = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif