#include "Boid.h"

Boid::Boid(const Vec2& position)
  : m_position(position),
  m_prevPosition(Vec2(0.0f, 0.0f)),
  m_speed(10.0f)
{}

Vec2
Boid::getDir() const
{
  return (m_position - m_prevPosition).normalize();
}

Vec2
Boid::seek(Vec2 const& currentPos,
           Vec2 const& destination,
           float const strength) const
{
  Vec2 const dirToDestination = destination - currentPos;

  return dirToDestination.normalize() * strength;
}


Vec2
Boid::flee(Vec2 const& currentPos,
           Vec2 const& positionToFleeFrom,
           float const strength,
           float const radius) const
{
  Vec2 const distanceToDestination = currentPos - positionToFleeFrom;

  if( distanceToDestination.length() < radius )
  {
    return this->seek(currentPos, positionToFleeFrom, strength);
  }

  return Vec2(0.0f, 0.0f);
}


Vec2
Boid::arrive(Vec2 const& currentPos,
             Vec2 const& destination,
             float const strength,
             float const radius) const
{
  Vec2 const distanceToDestination = destination - currentPos;
  float const distance = distanceToDestination.magnitude();

  if( distance < radius )
  {
    float const inverseRadius = 1.0f / radius;
    return this->seek(currentPos, destination, strength) * (inverseRadius * distance);
  }

  return this->seek(currentPos, destination, strength);
}

Vec2 //pursue
Boid::pursue(Vec2 const& currentPos,
             Boid const& target,
             const float deltaTime,
             float const strength) const
{
  Vec2 const targetPosition = target.m_position;

  Vec2 ProjectPos = targetPosition + (target.getDir() * target.m_speed * deltaTime);
  Vec2 const distanceFromTarget = (currentPos - targetPosition); 
  Vec2 const distanceFromProjection =  (currentPos - ProjectPos);
  if( distanceFromProjection.lengthSqr() < distanceFromTarget.lengthSqr() )
  {
    float const newVectorMagnitude = 1.0f / (distanceFromProjection.magnitude() * distanceFromTarget.inverseMagnitude());
        
    return this->seek(currentPos, ProjectPos * newVectorMagnitude, strength);
  }
  else
    return  this->seek(currentPos, ProjectPos, strength);
}

