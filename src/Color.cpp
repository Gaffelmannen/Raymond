#include "Color.h"

using color = Vector3;

double Color::clamp(double x) const
{
    double min = -infinity;
    double max = +infinity;
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

vector<int> Color::SetPixelColor(color pixelColor)
{
    vector<int> v;
    v.push_back(static_cast<int>(255.999 * pixelColor.x()));
    v.push_back(static_cast<int>(255.999 * pixelColor.y()));
    v.push_back(static_cast<int>(255.999 * pixelColor.z()));
    return v;
}

vector<int> Color::SetPixelColorAntialiasing(color pixelColor)
{
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    int redByte = int(256 * clamp(r));
    int greenByte = int(256 * clamp(g));
    int blueByte = int(256 * clamp(b));

    vector<int> v;
    v.push_back(redByte);
    v.push_back(greenByte);
    v.push_back(blueByte);
    return v;
}
