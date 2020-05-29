#include "vec2.h"
#include <cmath> // for std::sqrtf
#include <limits>// for std::numeric_limits

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

bool
vec2::operator==(vec2 const& other) const
{
  //controls how many digits of accuracy we check for
//  static constexpr int digitsBeforeTheDot = 6; // Threshold
  static constexpr float const minimalThreshold = 1.0f / 1000.0f;// 0.001
  vec2 const delta = this->subtract(other);

  if( std::fabsf(delta.x) <= minimalThreshold &&
     std::fabsf(delta.y) <= minimalThreshold )
  {
    return true;
  }

  //float const scaleEpsilonInX =
  //  std::numeric_limits<float>::epsilon() * std::fabsf(Sum.x);

  //float const scaleEpsilonInY =
  //  std::numeric_limits<float>::epsilon() * std::fabsf(Sum.y);

  //if( std::fabsf(delta.x) <= (scaleEpsilonInX * digitsBeforeTheDot) &&
  //   std::fabsf(delta.y) <= (scaleEpsilonInY * digitsBeforeTheDot) )
  //{
  //  return true;
  //}

  //else if( std::fabsf(delta.x) < std::numeric_limits<float>::min() &&
  //       std::fabsf(delta.y) < std::numeric_limits<float>::min() )
  //{
  //  return true;
  //}
      
  return false;
}

bool 
vec2::operator!=(vec2 const& other) const
{
  if(*this == other)
    return false;
      
  return true;
}


bool 
vec2::operator<(vec2 const& other) const
{
  if( this->magnitudeSqr() < other.magnitudeSqr() )
    return true;

  return false;
}

bool 
vec2::operator>(vec2 const& other) const
{

  if( this->magnitudeSqr() > other.magnitudeSqr() )
    return true;

  return false;
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

std::ostream& 
operator<<(std::ostream& os, vec2 const& vector)
{
  return os << '<' << vector.x << ", " << vector.y << '>';
}
