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

    void add(shared_ptr<Hittable> object) 
    {
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

        return hitAnything;
    }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
        HitRecord tempRecord;
        bool hitAnything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) 
        {
            if (object->hit(r, Interval(ray_t.min, closest_so_far), tempRecord)) 
            {
                hitAnything = true;
                closest_so_far = tempRecord.t;
                rec = tempRecord;
            }
        }

        return hitAnything;
    }
};

#endif