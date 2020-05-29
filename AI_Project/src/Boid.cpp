#include "..\include\Boid.h"

vec2
Boid::seek(vec2 const& currentPos,
           vec2 const& destination,
           float const strength) const
{
  vec2 const dirToDestination = destination - currentPos;

  return dirToDestination.normalize() * strength;
}

vec2
Boid::flee(vec2 const& currentPos,
           vec2 const& destination,
           float const strength,
           float const radius) const
{

  vec2 const distanceToDestination = destination - currentPos;

  if( distanceToDestination.lengthSqr() < (radius * radius) )
  {

    return  this->seek(currentPos, destination, strength) * -1.0f;
  }


  return vec2(0.0f, 0.0f);
}

vec2
Boid::arrive(vec2 const& currentPos,
             vec2 const& destination,
             float const strength,
             float const radius) const
{
  vec2 const distanceToDestination = destination - currentPos;
  float const distanceLengthSqr = distanceToDestination.lengthSqr();

  if( distanceLengthSqr < (radius * radius) )
  {
    float const inverseRadius = 1.0f / (radius * radius);
    return this->seek(currentPos, destination, strength) * (inverseRadius * distanceLengthSqr);
  }

  return this->seek(currentPos, destination, strength);
}
