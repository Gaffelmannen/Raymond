#include "rtweekend.h"

#include "FileManager.h"

#include "hittable.h"
#include "HittableList.h"
#include "sphere.h"
#include "Color.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

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

color colorOfTheRay(const Ray& ray, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(ray, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
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

vector<vector<int>> createCanvas()
{
    vector<vector<int>> canvas;

    for (int j = HEIGHT-1; j >= 0; --j)
    {
        cerr << "\rRemaining: ";
        cerr << j;
        cerr << " " << std::flush;

        for (int i = 0; i < WIDTH; ++i)
        {
            vector<int> row;

            auto red = double(i) / (WIDTH-1);
            auto green = double(j) / (HEIGHT-1);
            auto blue = 0.25;

            int r = static_cast<int>(255.999 * red);
            int g = static_cast<int>(255.999 * green);
            int b = static_cast<int>(255.999 * blue);

            row.push_back(r);
            row.push_back(g);
            row.push_back(b);
            canvas.push_back(row);
        }
    }

    cerr << endl << "Canvas Created." << endl;

    return canvas;
}

vector<vector<int>> rayTrace()
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

    for (int j = HEIGHT-1; j >= 0; --j)
    {
        cerr << "\rRemaining: ";
        cerr << j;
        cerr << " " << std::flush;

        for (int i = 0; i < WIDTH; ++i)
        {
            auto u = double(i) / (WIDTH - 1);
            auto v = double(j) / (HEIGHT - 1);

            Ray r = Ray
            (
                origin,
                (
                    lowerLeftCorner +
                    u * horizontal +
                    v * vertical
                )
            );

            color pixelColor = colorOfTheRay(r, world);
            vector<int> row = c->SetPixelColor(pixelColor);
            canvas.push_back(row);
        }
    }

    cerr << endl << "Canvas Created." << endl;

    delete c;

    return canvas;
}

int main()
{
    vector<vector<int>> canvas = rayTrace();

    FileManager* fm = new FileManager();
    fm->WriteToJpegFile("raymond", WIDTH, HEIGHT, canvas);
    delete fm;

    cout << "Party like it is 1999." << endl;
}
