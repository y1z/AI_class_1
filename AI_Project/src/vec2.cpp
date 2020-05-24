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



