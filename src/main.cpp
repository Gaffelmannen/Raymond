#include "FileManager.h"
#include "Camera.h"
#include "hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "sphere.h"

int main()
{
    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2));

    hittable_list world;
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5));
    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0));
    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    
    Camera cam = Camera(world);
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth  = 1280;
    cam.samplesPerPixel = 100;
    cam.maxDepth = 10;
    cam.reflectance = 0.5;

    cam.render();
}
