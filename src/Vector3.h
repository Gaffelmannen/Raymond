#ifndef VECTOR3
#define VECTOR3

#include <cmath>
#include <iostream>

#include "misc.h"

using std::sqrt;
using namespace std;    

class Vector3
{
    public:
    double e[3];
    
    Vector3() : e{ 0, 0, 0 } {}
    Vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}
    
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    
    Vector3 operator -() const { return Vector3(-e[0], -e[1], -e[2]); }
    double operator [](int i) const { return e[i]; }
    double& operator [](int i) { return e[i]; }
    
    Vector3 operator += (const Vector3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    
    Vector3 operator *= (const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    
    Vector3 operator /= (const double t)
    {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }
    
    double length() const
    {
        return sqrt(lengthSquared());
    }
    
    double lengthSquared() const
    {
        return
            e[0] * e[0] +
            e[1] * e[1] +
            e[2] * e[2];
    }

    bool nearZero() const 
    {
        auto s = 1e-8;
        return (
            std::fabs(e[0]) < s) && 
            (std::fabs(e[1]) < s) && 
            (std::fabs(e[2]) < s);
    }

    static Vector3 random() 
    {
        return Vector3(randomDouble(), randomDouble(), randomDouble());
    }

    static Vector3 random(double min, double max) 
    {
        return Vector3(randomDouble(min,max), randomDouble(min,max), randomDouble(min,max));
    }
};

using point3 = Vector3;
using color = Vector3;

inline ostream& operator << (ostream &stream, const Vector3 v)
{
    return
        stream << v.e[0] << " ";
        stream << v.e[1] << " ";
        stream << v.e[2];
}

inline Vector3 operator + (const Vector3& u, const Vector3& v)
{
    return Vector3
    (
        u.e[0] + v.e[0],
        u.e[1] + v.e[1],
        u.e[2] + v.e[2]
    );
}

inline Vector3 operator - (const Vector3& u, const Vector3& v)
{
    return Vector3
    (
        u.e[0] - v.e[0],
        u.e[1] - v.e[1],
        u.e[2] - v.e[2]
    );
}

inline Vector3 operator * (const Vector3& u, const Vector3& v)
{
    return Vector3
    (
        u.e[0] * v.e[0],
        u.e[1] * v.e[1],
        u.e[2] * v.e[2]
    );
}

inline Vector3 operator * (const double t, const Vector3& v)
{
    return Vector3
    (
        t*v.e[0],
        t*v.e[1],
        t*v.e[2]
    );
}

inline Vector3 operator * (Vector3 v, double t)
{
    return t * v;
}

inline Vector3 operator / (Vector3& v, double t)
{
    return (1/t) * v;
}

inline double scalarProduct(const Vector3& u, const Vector3& v)
{
    return
        u.e[0] * v.e[0] +
        u.e[1] * v.e[1] +
        u.e[2] * v.e[2];
}

inline Vector3 vectorProduct(const Vector3& u, const Vector3& v)
{
    return Vector3
    (
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

inline Vector3 unitVector(Vector3 v)
{
    return v / v.length();
}

inline Vector3 operator/(const Vector3& v, double t) 
{
    return (1/t) * v;
}

inline Vector3 random_unit_vector() 
{
    while (true) 
    {
        auto p = Vector3::random(-1, 1);
        auto lensq = p.lengthSquared();
        if (1e-160 < lensq && lensq <= 1)
        {
            return p / sqrt(lensq);
        }
    }
}

inline Vector3 randomOnHemisphere(const Vector3& normal) 
{
    Vector3 on_unit_sphere = random_unit_vector();
    if (scalarProduct(on_unit_sphere, normal) > 0.0)
    {
        return on_unit_sphere;;
    }
    else
    {
        return -on_unit_sphere;
    }
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) 
{
    return v - (2 * scalarProduct(v,n) * n );
}


#endif
