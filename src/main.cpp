#include "FileManager.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

bool rayHitsSphere(const point3& center, double radius, const Ray& ray)
{
    Vector3 originOffsetByCenter = ray.getOrigin() - center;
    auto x = scalarProduct(ray.getDirection(), ray.getDirection());
    auto y = 2.0 * scalarProduct(originOffsetByCenter, ray.getDirection());
    auto z = scalarProduct(originOffsetByCenter, originOffsetByCenter) - radius * radius;
    auto discriminant = y*y - 4 * x * z;
    return (discriminant > 0);
}

color colorOfTheRay(const Ray& ray)
{
    if(rayHitsSphere(point3(0, 0, -1), 0.5, ray))
    {
        return color(0, 1, 0);
    }
    Vector3 unitDirection = unitVector(ray.getDirection());
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return
        (1.0 - t) * color(1.0, 1.0, 1.0) +
        t * color(0.5, 0.7, 1.0);
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

            color pixelColor = colorOfTheRay(r);
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
