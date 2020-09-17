#pragma once

//------------------------------------------------------------------------
// Vector Class and vector functions
//------------------------------------------------------------------------
class Vector
{
public:
    float x;

    float y;

    float z;

    Vector();

    Vector(float xi, float yi, float zi);

    float Magnitude() const;

    void Normalize();

    void Reverse();

    Vector& operator+=(const Vector& u);

    Vector& operator-=(const Vector& u);

    Vector& operator*=(float s);

    Vector& operator/=(float s);

    Vector operator-() const;

    friend Vector operator+(const Vector& u, const Vector& v);

    friend Vector operator-(const Vector& u, const Vector& v);

    friend Vector operator^(const Vector& u, const Vector& v);

    friend float operator*(const Vector& u, const Vector& v);

    friend Vector operator*(float s, const Vector& u);

    friend Vector operator*(const Vector& u, float s);

    friend Vector operator/(const Vector& u, float s);

    static float TripleScalarProduct(const Vector& u, const Vector& v, const Vector& w);
};
