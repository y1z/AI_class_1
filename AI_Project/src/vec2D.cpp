#include "vec2D.h"

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



