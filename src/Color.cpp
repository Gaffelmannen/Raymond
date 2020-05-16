#include "Color.h"

vector<int> Color::SetPixelColor(color pixelColor)
{
    vector<int> v;
    v.push_back(static_cast<int>(255.999 * pixelColor.x()));
    v.push_back(static_cast<int>(255.999 * pixelColor.y()));
    v.push_back(static_cast<int>(255.999 * pixelColor.z()));
    return v;
}
