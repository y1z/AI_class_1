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

void 
vec2::operator+=(vec2 const& other)
{
  addToSelf(other);
}

vec2 
vec2::operator-(vec2 const& other) const
{
  return subtract(other);
}

void 
vec2::operator-=(vec2 const& other)
{
  subtractFromSelf(other);
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

void 
vec2::addToSelf(vec2 const& other)
{
  this->x += other.x;
  this->y += other.y;
}

void 
vec2::addToSelf(float const& x, float const& y)
{
  this->x += x;
  this->y += y;
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

void 
vec2::subtractFromSelf(vec2 const& other)
{
  this->x -= other.x;
  this->y -= other.y;
}

void 
vec2::subtractFromSelf(float const& x, float const& y)
{
  this->x = x;
  this->y = y;
}


