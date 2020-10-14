#pragma once

#include "Vector.h"

class Matrix3x3
{
public:
    float e11, e12, e13, e21, e22, e23, e31, e32, e33;

    Matrix3x3();

    Matrix3x3(float r1c1, float r1c2, float r1c3,
              float r2c1, float r2c2, float r2c3,
              float r3c1, float r3c2, float r3c3);

    float det() const;

    Matrix3x3 Transpose() const;

    Matrix3x3 Inverse() const;

    Matrix3x3 operator+=(const Matrix3x3& m);

    Matrix3x3 operator-=(const Matrix3x3& m);

    Matrix3x3 operator*=(float s);

    Matrix3x3 operator/=(float s);

    friend Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2);

    friend Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2);

    friend Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);

    friend Matrix3x3 operator*(const Matrix3x3& m, float s);

    friend Matrix3x3 operator*(float s, const Matrix3x3& m);

    friend Vector operator*(const Matrix3x3& m, const Vector& v);

    friend Vector operator*(const Vector& v, const Matrix3x3& m);
};
