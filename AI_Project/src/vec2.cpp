#include "Vec2.h"
#include <cmath>  // for std::sqrtf
#include <limits>// for std::numeric_limits

Vec2::Vec2(float const x_,
           float const y_ )
  : x(x_),
  y(y_)
{}
const Vec2 Vec2::upVector2 = Vec2(0.f,1.0f);

const Vec2 Vec2::downVector2 = Vec2(0.f,-1.0f);

const Vec2 Vec2::leftVector2 = Vec2(1.0f,0.0f);

const Vec2 Vec2::rightVector2 = Vec2(-1.0f,0.0f);

const Vec2 Vec2::zeroVector2 = Vec2(0.0f,0.0f);

const Vec2 Vec2::oneVector2 = Vec2(1.0f,1.0f);

const Vec2 Vec2::minVector2 = Vec2(std::numeric_limits<float>::min(),std::numeric_limits<float>::min());

const Vec2 Vec2::maxVector2 = Vec2( std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

const Vec2 Vec2::lowestVector2 = Vec2( std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

const Vec2 Vec2::epsilonVector2 = Vec2(std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::epsilon());

Vec2
Vec2::operator+(Vec2 const& other) const
{
  return add(other);
}

Vec2&
Vec2::operator+=(Vec2 const& other)
{
  return addToSelf(other);
}

Vec2
Vec2::operator-(Vec2 const& other) const
{
  return subtract(other);
}


Vec2&
Vec2::operator-=(Vec2 const& other)
{
  return  subtractFromSelf(other);
}

Vec2
Vec2::operator*(float const scalar) const
{
  return mulScalar(scalar);
}

Vec2&
Vec2::operator*=(float const scalar)
{
  return mulSelfByScalar(scalar);
}

float
Vec2::operator*(Vec2 const& other) const
{
  return dot(other);
}

bool
Vec2::operator==(Vec2 const& other) const
{
  //controls how many digits of accuracy we check for
  static constexpr int unitsInLastPlace = 5;

  Vec2 const delta = this->subtract(other);
  Vec2 const sum = this->add(other);

  float const scaleEpsilonInX =
    std::numeric_limits<float>::epsilon() * std::fabsf(sum.x);

  float const scaleEpsilonInY =
    std::numeric_limits<float>::epsilon() * std::fabsf(sum.y);

  if( std::fabsf(delta.x) <= (scaleEpsilonInX * unitsInLastPlace) &&
     std::fabsf(delta.y) <= (scaleEpsilonInY * unitsInLastPlace) )
  {
    return true;
  }

  else if( std::fabsf(delta.x) < std::numeric_limits<float>::min() &&
          std::fabsf(delta.y) < std::numeric_limits<float>::min() )
  {
    return true;
  }

  return false;
}

bool
Vec2::operator!=(Vec2 const& other) const
{
  return !(*this == other);
}

bool
Vec2::operator<(Vec2 const& other) const
{
  return this->magnitudeSqr() < other.magnitudeSqr();
}

bool
Vec2::operator>(Vec2 const& other) const
{
  return this->magnitudeSqr() > other.magnitudeSqr();
}

Vec2
Vec2::add(Vec2 const& other) const
{
  return Vec2(x + other.x,y + other.y);
}

Vec2
Vec2::add(float const x_, float const y_) const
{
  return Vec2(x + x_, y + y_);
}

Vec2&
Vec2::addToSelf(Vec2 const& other)
{
  return (*this = add(other));
}

Vec2&
Vec2::addToSelf (float const x_, float const y_)
{
  return (*this = add(x_, y_));
}

Vec2
Vec2::subtract(Vec2 const& other) const
{
  return Vec2(x - other.x, this->y - other.y);
}

Vec2
Vec2::subtract(float const x_, float const y_) const
{
  return Vec2(this->x - x_, this->y - y_);
}

Vec2&
Vec2::subtractFromSelf(Vec2 const& other)
{
  return (*this = subtract(other));
}

Vec2&
Vec2::subtractFromSelf(float const x_, float const y_)
{
  return (*this = subtract(x_, y_));
}

float
Vec2::dot(Vec2 const& other) const
{
  return (x * other.x) + (y * other.y);
}

Vec2
Vec2::mulScalar(float const scalar) const
{
  return Vec2(x * scalar, y * scalar);
}

Vec2&
Vec2::mulSelfByScalar(float const scalar)
{
  return (*this = mulScalar(scalar));
}

float
Vec2::magnitude() const
{
  return std::sqrtf((x * x) + (y * y));
}

float
Vec2::length() const
{
  return magnitude();
}

float
Vec2::magnitudeSqr() const
{
  return (this->x * this->x) + (this->y + this->y);
}

float
Vec2::lengthSqr() const
{
  return magnitudeSqr();
}

float
Vec2::inverseMagnitude() const
{
  float const mag = magnitude();
  return (mag >= std::numeric_limits<float>::epsilon())
    ? 1.0f / mag
    : 0.0f;
}

float 
Vec2::inverseLength() const
{
  return inverseMagnitude();
}

Vec2
Vec2::normalize() const
{
  float const inverMag = inverseMagnitude();

  return Vec2(x * inverMag, this->y * inverMag);
}

Vec2&
Vec2::normalizeSelf()
{
  return (*this = normalize());
}

Vec2
Vec2::rotate(float const radians) const
{
  return Vec2((std::cosf(radians) * this->x) - (std::sinf(radians) * this->y),
              (std::sinf(radians) * this->x) + (std::cosf(radians) * this->y));
}

Vec2&
Vec2::rotateSelfBy(float const radians)
{
  return (*this = rotate(radians));
}

float 
Vec2::getAngle() const
{
  return std::atan2f(y,x);
}

Vec2 
Vec2::perpendicularCounterClockWise() const
{
  return Vec2(-y, x);
}

Vec2 
Vec2::perpendicularClockWise() const
{
  return Vec2(y,-x );
}

Vec2&
Vec2::selfPerpendicularCounterClockWise()
{
  return (*this = perpendicularCounterClockWise());
}

Vec2&
Vec2::selfPerpendicularClockWise()
{
  return (*this = perpendicularClockWise());
}

Vec2 
Vec2::projectOnTo(const Vec2& projectedOn) const
{
  return projectedOn * (projectedOn.dot(*this) / projectedOn.magnitudeSqr());
}

Vec2 
Vec2::truncate(const float magnitude) const
{
  return normalize() * magnitude;
}

Vec2&
Vec2::truncateSelf(const float magnitude)
{
  return (*this = truncate(magnitude));
}

std::ostream&
operator<<(std::ostream& os, Vec2 const& vector)
{
  return os << '<' << vector.x << ", " << vector.y << '>';
}
