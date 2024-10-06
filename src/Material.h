#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class Material 
{
    public:
        virtual ~Material() = default;

        virtual bool scatter(
            const Ray& r_in, 
            const HitRecord& rec, 
            color& attenuation, 
            Ray& scattered
        ) const 
        {
            return false;
        }
};

class Lambertian : public Material 
{
    private:
        color albedo;
    public:
        Lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(
            const Ray& r_in, 
            const HitRecord& rec, 
            color& attenuation, 
            Ray& scattered
        ) const override 
        {
            auto scatterDirection = rec.normal + random_unit_vector();

            if (scatterDirection.nearZero())
            {
                scatterDirection = rec.normal;
            }

            scattered = Ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }
};

class Metal : public Material 
{
    public:
        Metal(const color& albedo) : albedo(albedo) {}

        bool scatter(
            const Ray& rayIn, 
            const HitRecord& rec,
            color& attenuation,
            Ray& scattered
        ) const override 
        {
            Vector3 reflected = reflect(rayIn.getDirection(), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }

    private:
        color albedo;
};

#endif