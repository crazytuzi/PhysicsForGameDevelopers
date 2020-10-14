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

    friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);

    friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);

    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

    friend Quaternion operator*(const Quaternion& q, float s);

    friend Quaternion operator*(float s, const Quaternion& q);

    friend Quaternion operator*(const Quaternion& q, const Vector& v);

    friend Quaternion operator*(const Vector& v, const Quaternion& q);

    friend Quaternion operator/(const Quaternion& q, float s);

    static Quaternion MakeQuaternionFromEulerAngles(float x, float y, float z);

    static Vector MakeEulerAnglesFromQuaternion(const Quaternion& q);

private:
    static float DegreesToRadians(float deg);

    static float RadiansToDegrees(float rad);
};
