#include "FileManager.h"
#include "Camera.h"

int main()
{
    hittable_list world;
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth  = 1280;

    cam.render(world);
}
