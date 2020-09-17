#include "Vector.h"

#include <complex>

const float tol = 0.0001f;

Vector::Vector() : x(0), y(0), z(0)
{
}

Vector::Vector(const float xi, const float yi, const float zi): x(xi), y(yi), z(zi)
{
}

float Vector::Magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

void Vector::Normalize()
{
    auto m = std::sqrt(x * x + y * y + z * z);

    if (m <= tol)
    {
        m = 1.f;
    }

    x /= m;

    y /= m;

    z /= m;

    if (std::fabs(x) < tol)
    {
        x = 0.f;
    }

    if (std::fabs(y) < tol)
    {
        y = 0.f;
    }

    if (std::fabs(z) < tol)
    {
        z = 0.f;
    }
}

void Vector::Reverse()
{
    x = -x;

    y = -y;

    z = -z;
}

Vector& Vector::operator+=(const Vector& u)
{
    x += u.x;

    y += u.y;

    z += u.z;

    return *this;
}

Vector& Vector::operator-=(const Vector& u)
{
    x -= u.x;

    y -= u.y;

    z -= u.z;

    return *this;
}

Vector& Vector::operator*=(const float s)
{
    x *= s;

    y *= s;

    z *= s;

    return *this;
}

Vector& Vector::operator/=(const float s)
{
    x /= s;

    y /= s;

    z /= s;

    return *this;
}

Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
}

Vector operator+(const Vector& u, const Vector& v)
{
    return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector operator-(const Vector& u, const Vector& v)
{
    return Vector(u.x - v.x, u.x - v.x, u.z - v.z);
}

Vector operator^(const Vector& u, const Vector& v)
{
    return Vector(u.y * v.z - u.z * v.y,
                  -u.x * v.z + u.z * v.x,
                  u.x * v.y - u.y * v.x);
}

float operator*(const Vector& u, const Vector& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector operator*(const float s, const Vector& u)
{
    return Vector(u.x * s, u.y * s, u.z * s);
}

Vector operator*(const Vector& u, const float s)
{
    return Vector(u.x * s, u.y * s, u.z * s);
}

Vector operator/(const Vector& u, const float s)
{
    return Vector(u.x / s, u.y / s, u.z / s);
}

float Vector::TripleScalarProduct(const Vector& u, const Vector& v, const Vector& w)
{
    return u.x * (v.y * w.z - v.z * w.y) +
        u.y * (-v.x * w.z + v.z * w.x) +
        u.z * (v.x * w.y - v.y * w.x);
}
