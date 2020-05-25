#include "vec2.h"
#include <cmath>

vec2::vec2()
  :x(0.0f),
  y(0.0f)
{}

vec2::vec2(float const& X,
           float const& Y)
  : x(X),
  y(Y)
{}

vec2
vec2::operator+(vec2 const& other) const
{
  return add(other);
}

vec2&
vec2::operator+=(vec2 const& other)
{
  return addToSelf(other);
}

vec2
vec2::operator-(vec2 const& other) const
{
  return subtract(other);
}

vec2&
vec2::operator-=(vec2 const& other)
{
  return  subtractFromSelf(other);
}

vec2
vec2::operator*(float const& scalar) const
{
  return mulScalar(scalar);
}

vec2&
vec2::operator*=(float const& scalar)
{
  return mulSelfByScalar(scalar);
}

float
vec2::operator*(vec2 const& other) const
{
  return dot(other);
}

vec2
vec2::add(vec2 const& other) const
{
  return vec2(this->x + other.x, this->y + other.y);
}

vec2
vec2::add(float const& x, float const& y) const
{
  return vec2(this->x + x, this->y + y);
}

vec2&
vec2::addToSelf(vec2 const& other)
{
  this->x += other.x;
  this->y += other.y;
  return *this;
}

vec2&
vec2::addToSelf(float const& x, float const& y)
{
  this->x += x;
  this->y += y;
  return *this;
}

vec2
vec2::subtract(vec2 const& other) const
{
  return vec2(this->x - other.x, this->y - other.y);
}

vec2
vec2::subtract(float const& x, float const& y) const
{
  return vec2(this->x - x, this->y - y);
}

vec2&
vec2::subtractFromSelf(vec2 const& other)
{
  this->x -= other.x;
  this->y -= other.y;
  return *this;
}

vec2&
vec2::subtractFromSelf(float const& x, float const& y)
{
  this->x = x;
  this->y = y;
  return *this;
}

float
vec2::dot(vec2 const& other) const
{
  return (this->x * other.x) + (this->y * other.y);
}

vec2
vec2::mulScalar(float const& scalar) const
{
  return vec2(this->x * scalar, this->y * scalar);
}

vec2&
vec2::mulSelfByScalar(float const& scalar)
{
  this->x *= scalar;
  this->y *= scalar;
  return *this;
}

float
vec2::magnitude() const
{
  return std::sqrtf((this->x * this->x) + (this->y * this->y));
}

float
vec2::length() const
{
  return magnitude();
}

float
vec2::magnitudeSqr() const
{
  return (this->x * this->x) + (this->y + this->y);
}

float
vec2::lengthSqr() const
{
  return magnitudeSqr();
}

float
vec2::inverseMagnitude() const
{
  return 1.0f / magnitude();
}

vec2
vec2::normalize() const
{
  float const inverMag = inverseMagnitude();

  return vec2(this->x * inverMag, this->y * inverMag);
}

vec2&
vec2::normalizeSelf()
{
  float const inverMag = inverseMagnitude();
  this->x *= inverMag;
  this->y *= inverMag;
  return *this;
}

vec2
vec2::rotate(float const& radians) const
{
  float const AngleInX = this->x * radians;
  float const AngleInY = this->y * radians;

  return vec2(std::cosf(AngleInX) - std::sinf(AngleInY),
              std::sinf(AngleInX) + std::cosf(AngleInY));
}

vec2&
vec2::rotateSelfBy(float const& radians)
{
  float const AngleInX = this->x * radians;
  float const AngleInY = this->y * radians;
  this->x = std::cosf(AngleInX) - std::sinf(AngleInY);
  this->y = std::sinf(AngleInX) + std::cosf(AngleInY);
  return *this;
}

