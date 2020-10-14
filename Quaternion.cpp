#include "Quaternion.h"

#include <complex>

const float tol = 0.0001f;

const float pi = 3.1415926f;

Quaternion::Quaternion(): n(0), v(0, 0, 0)
{
}

Quaternion::Quaternion(const float e0, const float e1, const float e2, const float e3): n(e0), v(e1, e2, e3)
{
}

float Quaternion::Magnitude() const
{
    return std::sqrt(n * n + v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector Quaternion::GetVector() const
{
    return v;
}

float Quaternion::GetScalar() const
{
    return n;
}

float Quaternion::GetAngle() const
{
    return 2 * std::acos(n);
}

Vector Quaternion::GetAxis() const
{
    const auto m = v.Magnitude();

    return m <= tol ? Vector() : v / m;
}

Quaternion Quaternion::Rotate(const Quaternion& q) const
{
    return *this * q * ~*this;
}

Vector Quaternion::Rotate(const Vector& v) const
{
    return (*this * v * ~*this).GetVector();
}

Quaternion Quaternion::operator+=(const Quaternion& q)
{
    n += q.n;

    v.x += q.v.x;

    v.y += q.v.y;

    v.z += q.v.z;

    return *this;
}

Quaternion Quaternion::operator-=(const Quaternion& q)
{
    n -= q.n;

    v.x -= q.v.x;

    v.y -= q.v.y;

    v.z -= q.v.z;

    return *this;
}

Quaternion Quaternion::operator*=(const float s)
{
    n *= s;

    v.x *= s;

    v.y *= s;

    v.z *= s;

    return *this;
}

Quaternion Quaternion::operator/=(const float s)
{
    n /= s;

    v.x /= s;

    v.y /= s;

    v.z /= s;

    return *this;
}

Quaternion Quaternion::operator~() const
{
    return Quaternion(n, -v.x, -v.y, -v.z);
}

Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.n + q2.n,
                      q1.v.x + q2.v.x,
                      q1.v.y + q2.v.y,
                      q1.v.z + q2.v.z);
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.n - q2.n,
                      q1.v.x - q2.v.x,
                      q1.v.y - q2.v.y,
                      q1.v.z - q2.v.z);
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
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

Quaternion operator*(const Quaternion& q, const float s)
{
    return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
}

Quaternion operator*(const float s, const Quaternion& q)
{
    return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
}

Quaternion operator*(const Quaternion& q, const Vector& v)
{
    return Quaternion(-(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
                      q.n * v.x + q.v.y * v.z - q.v.z * v.y,
                      q.n * v.y + q.v.z * v.x - q.v.x * v.z,
                      q.n * v.z + q.v.x * v.y - q.v.y * v.x);
}

Quaternion operator*(const Vector& v, const Quaternion& q)
{
    return Quaternion(-(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
                      q.n * v.x + q.v.z * v.y - q.v.y * v.z,
                      q.n * v.y + q.v.x * v.z - q.v.z * v.x,
                      q.n * v.z + q.v.y * v.x - q.v.x * v.y);
}

Quaternion operator/(const Quaternion& q, const float s)
{
    return Quaternion(q.n / s, q.v.x / s, q.v.y / s, q.v.z / s);
}

Quaternion Quaternion::MakeQuaternionFromEulerAngles(const float x, const float y, const float z)
{
    const auto roll = DegreesToRadians(x);

    const auto pitch = DegreesToRadians(y);

    const auto yaw = DegreesToRadians(z);

    const auto cyaw = cos(0.5f * yaw);

    const auto cpitch = cos(0.5f * pitch);

    const auto croll = cos(0.5f * roll);

    const auto syaw = sin(0.5f * yaw);

    const auto spitch = sin(0.5f * pitch);

    const auto sroll = sin(0.5f * roll);

    const auto cyawcpitch = cyaw * cpitch;

    const auto syawspitch = syaw * spitch;

    const auto cyawspitch = cyaw * spitch;

    const auto syawcpitch = syaw * cpitch;

    return Quaternion(cyawcpitch * croll + syawspitch * sroll,
                      cyawcpitch * sroll - syawspitch * croll,
                      cyawspitch * croll + syawcpitch * sroll,
                      syawcpitch * croll - cyawspitch * sroll);
}

Vector Quaternion::MakeEulerAnglesFromQuaternion(const Quaternion& q)
{
    const auto q00 = q.n * q.n;

    const auto q11 = q.v.x * q.v.x;

    const auto q22 = q.v.y * q.v.y;

    const auto q33 = q.v.z * q.v.z;

    const auto r11 = q00 + q11 - q22 - q33;

    const auto r21 = 2 * (q.v.x * q.v.y + q.n * q.v.z);

    const auto r31 = 2 * (q.v.x * q.v.z - q.n * q.v.y);

    const auto r32 = 2 * (q.v.y * q.v.z + q.n * q.v.x);

    const auto r33 = q00 - q11 - q22 + q33;

    if (fabs(r31) > 0.999999)
    {
        const auto r12 = 2 * (q.v.x * q.v.y - q.n * q.v.z);

        const auto r13 = 2 * (q.v.x * q.v.z + q.n * q.v.y);

        return Vector(RadiansToDegrees(0.0f),
                      RadiansToDegrees(-(pi / 2) * r31 / fabs(r31)),
                      RadiansToDegrees(atan2(-r12, -r31 * r13)));
    }

    return Vector(RadiansToDegrees(atan2(r32, r33)),
                  RadiansToDegrees(asin(-r31)),
                  RadiansToDegrees(atan2(r21, r11)));
}

float Quaternion::DegreesToRadians(const float deg)
{
    return deg * pi / 180.f;
}

float Quaternion::RadiansToDegrees(const float rad)
{
    return rad * 180.f / pi;
}
