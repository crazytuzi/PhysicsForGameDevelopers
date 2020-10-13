#pragma once

#include "Vector.h"

class Quaternion
{
public:
    float n;

    Vector v;

    Quaternion();

    Quaternion(float e0, float e1, float e2, float e3);

    float Magnitude() const;

    Vector GetVector() const;

    float GetScalar() const;

    float GetAngle() const;

    Vector GetAxis() const;

    Quaternion Rotate(const Quaternion& q) const;

    Vector Rotate(const Vector& v) const;

    Quaternion operator+=(const Quaternion& q);

    Quaternion operator-=(const Quaternion& q);

    Quaternion operator*=(float s);

    Quaternion operator/=(float s);

    Quaternion operator~() const;

    friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
    {
        return Quaternion(q1.n + q2.n,
                          q1.v.x + q2.v.x,
                          q1.v.y + q2.v.y,
                          q1.v.z + q2.v.z);
    }

    friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
    {
        return Quaternion(q1.n - q2.n,
                          q1.v.x - q2.v.x,
                          q1.v.y - q2.v.y,
                          q1.v.z - q2.v.z);
    }

    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
    {
        return Quaternion(q1.n * q2.n - q1.v.x * q2.v.x
                          - q1.v.y * q2.v.y - q1.v.z * q2.v.z,
                          q1.n * q2.v.x + q1.v.x * q2.n
                          + q1.v.y * q2.v.z - q1.v.z * q2.v.y,
                          q1.n * q2.v.y + q1.v.y * q2.n
                          + q1.v.z * q2.v.x - q1.v.x * q2.v.z,
                          q1.n * q2.v.z + q1.v.z * q2.n
                          + q1.v.x * q2.v.y - q1.v.y * q2.v.x);
    }

    friend Quaternion operator*(const Quaternion& q, const float s)
    {
        return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
    }

    friend Quaternion operator*(const float s, const Quaternion& q)
    {
        return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
    }

    friend Quaternion operator*(const Quaternion& q, const Vector& v)
    {
        return Quaternion(-(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
                          q.n * v.x + q.v.y * v.z - q.v.z * v.y,
                          q.n * v.y + q.v.z * v.x - q.v.x * v.z,
                          q.n * v.z + q.v.x * v.y - q.v.y * v.x);
    }

    friend Quaternion operator*(const Vector& v, const Quaternion& q)
    {
        return Quaternion(-(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
                          q.n * v.x + q.v.z * v.y - q.v.y * v.z,
                          q.n * v.y + q.v.x * v.z - q.v.z * v.x,
                          q.n * v.z + q.v.y * v.x - q.v.x * v.y);
    }

    friend Quaternion operator/(const Quaternion& q, const float s)
    {
        return Quaternion(q.n / s, q.v.x / s, q.v.y / s, q.v.z / s);
    }

    static Quaternion MakeQuaternionFromEulerAngles(float x, float y, float z);

    static Vector MakeEulerAnglesFromQuaternion(const Quaternion& q);

private:
    static float DegreesToRadians(float deg);

    static float RadiansToDegrees(float rad);
};
