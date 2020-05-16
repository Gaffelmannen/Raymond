#include "FileManager.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

const int WIDTH = 800;
const int HEIGHT = 600;

color colorOfTheRay(const Ray& r)
{
    Vector3 unitDirection = unitVector(r.getDirection());
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
    /*
    vector<vector<int>> canvas = createCanvas();
    
    FileManager* fm = new FileManager();
    fm->WriteToJpegFile("test", WIDTH, HEIGHT, canvas);
    delete fm;
    */
    
    vector<vector<int>> canvas = rayTrace();
    
    FileManager* fm = new FileManager();
    fm->WriteToJpegFile("test", WIDTH, HEIGHT, canvas);
    delete fm;

    cout << "Party like it is 1999." << endl;
}
