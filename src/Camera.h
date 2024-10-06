#ifndef CAMERA_H
#define CAMERA_H

#include "FileManager.h"
#include "hittable.h"
#include "HittableList.h"
#include "Color.h"
#include "sphere.h"
#include "Material.h"


/*
#include "hittable.h"
#include "HittableList.h"
#include "sphere.h"
#include "Material.h"
#include "Color.h"
#include "misc.h"
*/


class Camera 
{
    public:
        double aspectRatio;
        int imageWidth;
        int samplesPerPixel;
        int maxDepth;
        double reflectance;

        void render(const Hittable& world) 
        {
            initialize();
            createCanvas(world);

            vector<vector<int>> canvas = rayTrace(maxDepth);

            FileManager* fm = new FileManager();
            fm->WriteToJpegFile("raymond", imageWidth, imageHeight, canvas);
            delete fm;
            cout << "Party like it is 1999." << endl;
        }

    private:
        int imageHeight;
        double pixelSamplesScale;
        point3 center;
        point3 pixel00Location;
        Vector3 pixelDeltaU;
        Vector3 pixelDeltaV;

        void initialize() 
        {
            imageHeight = int(imageWidth / aspectRatio);
            imageHeight = (imageHeight < 1) ? 1 : imageHeight;

            pixelSamplesScale = 1.0 / samplesPerPixel;

            center = point3(0, 0, 0);

            auto focalLength = 1.0;
            auto viewportHeight = 2.0;
            auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);

            auto viewportU = Vector3(viewportWidth, 0, 0);
            auto viewportV = Vector3(0, -viewportHeight, 0);

            pixelDeltaU = viewportU / imageWidth;
            pixelDeltaV = viewportV / imageHeight;

            auto viewportUpperLeft =
                center - 
                Vector3(0, 0, focalLength) - 
                viewportU/2 - 
                viewportV/2;

            pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
        }

        double rayHitsSphere(const point3& center, double radius, const Ray& ray)
        {
            Vector3 originOffsetByCenter = ray.getOrigin() - center;
            auto x = ray.getDirection().lengthSquared();
            auto half_of_y = scalarProduct(originOffsetByCenter, ray.getDirection());
            auto z = originOffsetByCenter.lengthSquared() - radius*radius;
            auto discriminant = half_of_y * half_of_y - x*z;

            if (discriminant < 0)
            {
                return -1.0;
            }
            else
            {
                return (-half_of_y - sqrt(discriminant)) / x;
            }
        }

        color colorOfTheRay(const Ray& ray, int depth, const Hittable& world)
        {
            if (depth <= 0)
            {
                return color(0,0,0);
            }

            HitRecord rec;
            if (world.hit(ray, Interval(0.001, infinity), rec)) 
            {
                Vector3 direction = rec.normal + random_unit_vector();
                return reflectance * colorOfTheRay(Ray(rec.p, direction), depth-1, world);
                /*
                Ray scattered;
                color attenuation;
                if (rec.material->scatter(ray, rec, attenuation, scattered))
                {
                    return attenuation * colorOfTheRay(scattered, depth - 1, world);
                }
                return color(0,0,0);
                */
            }

            auto t = rayHitsSphere(point3(0, 0, -1), 0.5, ray);
            if( t > 0.0)
            {
                Vector3 N = unitVector(ray.at(t) - Vector3(0, 0, -1));
                return 0.5 * color( N.x() + 1, N.y() + 1, N.z() + 1 );
            }
            Vector3 unitDirection = unitVector(ray.getDirection());
            t = 0.5 * (unitDirection.y() + 1.0);
            return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
        }

        vector<vector<int>> createCanvas(const Hittable &world)
        {
            vector<vector<int>> canvas;

            for (int j = imageHeight-1; j >= 0; --j)
            {
                cerr << "\rRemaining: ";
                cerr << j;
                cerr << " " << std::flush;

                for (int i = 0; i < imageWidth; ++i)
                {
                    auto red = double(i) / (imageWidth-1);
                    auto green = double(j) / (imageHeight-1);
                    auto blue = 0.25;

                    int r = static_cast<int>(255.999 * red);
                    int g = static_cast<int>(255.999 * green);
                    int b = static_cast<int>(255.999 * blue);

                    color pixelColor(0,0,0);
                    for (int sample = 0; sample < samplesPerPixel; sample++) 
                    {
                        Ray r = getRay(i, j);
                        pixelColor += colorOfTheRay(r, maxDepth, world);
                    }

                    Color c;
                    vector<int> row = c.SetPixelColorAntialiasing(
                        pixelSamplesScale * pixelColor
                    );

                    row.push_back(r);
                    row.push_back(g);
                    row.push_back(b);

                    canvas.push_back(row);
                }
            }

            cerr << endl << "Canvas Created." << endl;

            return canvas;
        }

        vector<vector<int>> rayTrace(int depth)
        {
            vector<vector<int>> canvas;
            Color* c = new Color();

            point3 origin(0.0, 0.0, 0.0);
            Vector3 horizontal(4.0, 0.0, 0.0);
            Vector3 vertical(0.0, 2.25, 0.0);
            point3 lowerLeftCorner = origin -
                                    horizontal/2 -
                                    vertical/2 -
                                    Vector3(0,0,1);

            hittable_list world;
            world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
            world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));

            for (int j = imageHeight-1; j >= 0; --j)
            {
                cerr << "\rRemaining: ";
                cerr << j;
                cerr << " " << std::flush;

                for (int i = 0; i < imageWidth; ++i)
                {
                    auto u = double(i) / (imageWidth - 1);
                    auto v = double(j) / (imageHeight - 1);

                    Ray r = Ray
                    (
                        origin,
                        (
                            lowerLeftCorner +
                            u * horizontal +
                            v * vertical
                        )
                    );

                    color pixelColor = colorOfTheRay(r, depth-1, world);
                    vector<int> row = c->SetPixelColor(pixelColor);
                    canvas.push_back(row);
                }
            }

            cerr << endl << "Canvas Created." << endl;

            delete c;

            return canvas;
        }

        Ray getRay(int i, int j) const 
        {
            auto offset = sampleSquare();
            auto pixel_sample = 
                pixel00Location + 
                ((i + offset.x()) * pixelDeltaU)+ 
                ((j + offset.y()) * pixelDeltaV);

            auto rayOrigin = center;
            auto rayDirection = pixel_sample - rayOrigin;

            return Ray(rayOrigin, rayDirection);
        }

        Vector3 sampleSquare() const 
        {
            return Vector3(
                randomDouble() - 0.5, 
                randomDouble() - 0.5,
                0);
        }
};

#endif