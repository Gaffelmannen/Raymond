#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "facet.h"


class Sphere : public Hittable {
    public:
        Sphere(point3 _center, double _radius) : center(_center), radius(_radius) 
        {

        }

        Sphere(
            const point3& center, 
            double radius, 
            shared_ptr<Material> mat)
        : 
            center(center), 
            radius(std::fmax(0,radius)),
            material(mat)
        {}

        bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override 
        {
            Vector3 oc = r.getOrigin() - center;
            auto a = r.getDirection().lengthSquared();
            auto half_b = scalarProduct(oc, r.getDirection());
            auto c = oc.lengthSquared() - radius*radius;

            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) 
            {
                return false;
            }
            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (-half_b - sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root) 
            {
                root = (-half_b + sqrtd) / a;
                if (root <= ray_tmin || ray_tmax <= root)
                {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            Vector3 outwardNormal = (rec.p - center) / radius;
            rec.set_face_normal(r, outwardNormal);

            return true;
      }

        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override 
        {
            Vector3 oc = r.getOrigin() - center;
            auto a = r.getDirection().lengthSquared();
            auto half_b = scalarProduct(oc, r.getDirection());
            auto c = oc.lengthSquared() - radius*radius;

            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) 
            {
                return false;
            }
            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (-half_b - sqrtd) / a;
            if (!ray_t.surrounds(root))
            {
                root = (-half_b + sqrtd) / a;
                if (!ray_t.surrounds(root))
                {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            Vector3 outwardNormal = (rec.p - center) / radius;
            rec.set_face_normal(r, outwardNormal);
            rec.material = material;

            return true;
        }

  private:
        point3 center;
        double radius;
        shared_ptr<Material> material;
};

#endif


