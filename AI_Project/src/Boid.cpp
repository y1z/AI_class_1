#include "Boid.h"

Boid::Boid(const Vec2& position)
  :
  m_shape(100.0f),
  m_position(position),
  m_prevPosition(Vec2(0.0f, 0.0f)),
  m_speed(10.0f),
  m_wanderTime(0.0f),
  m_isWandering(false)

{
  m_shape.setFillColor(sf::Color::Blue);
}

void
Boid::init(Vec2 const& position,
           const float speed,
           const float radius,
           const sf::Color boidColor)
{
  m_position = position;
  m_prevPosition = Vec2(0.0f, 0.0f);
  m_speed = speed;
  m_shape.setRadius(radius);
  m_shape.setFillColor(boidColor);
  m_isWandering = false;
}

Vec2
Boid::getDir() const
{
  return (m_position - m_prevPosition).normalize();
}

Vec2
Boid::seek(const Vec2& currentPos,
           const Vec2& destination,
           const float strength) const
{
  Vec2 const dirToDestination = destination - currentPos;

  return dirToDestination.normalize() * strength;
}

Vec2
Boid::seek(const Boid& seekerBoid,
           const Boid& targetBoid,
           const float strength) const
{
  return this->seek(seekerBoid.m_position, targetBoid.m_position, strength);
}


Vec2
Boid::flee(const Vec2& currentPos,
           const Vec2& positionToFleeFrom,
           const float strength,
           const float radius) const
{
  Vec2 const distanceToDestination = currentPos - positionToFleeFrom;

  if( distanceToDestination.length() < radius )
  {
    return this->seek(currentPos, positionToFleeFrom, strength);
  }

  return Vec2(0.0f, 0.0f);
}


Vec2
Boid::arrive(const Vec2& currentPos,
             const Vec2& destination,
             const float  strength,
             const float  radius) const
{
  Vec2 const distanceToDestination = destination - currentPos;
  const float  distance = distanceToDestination.magnitude();

  if( distance < radius )
  {
    const float  inverseRadius = 1.0f / radius;
    return this->seek(currentPos, destination, strength) * (inverseRadius * distance);
  }

  return this->seek(currentPos, destination, strength);
}

Vec2
Boid::pursue(const Vec2& currentPos,
             const Boid& target,
             const float predictionTime,
             const float strength)const
{
  Vec2 const projectedRadius = target.getDir() * target.m_speed * predictionTime;

  Vec2 const projectPos = target.m_position + projectedRadius;

  Vec2 const distanceFromTarget = target.m_position - currentPos;

  Vec2 const distanceFromProjection = projectPos - currentPos;

  if( distanceFromProjection.lengthSqr() < distanceFromTarget.lengthSqr() )
  {
    const float  radiusReduction = distanceFromProjection.lengthSqr() / distanceFromTarget.lengthSqr();
    return this->seek(currentPos, projectPos + (projectedRadius * radiusReduction), strength);
  }
  else
    return  this->seek(currentPos, projectPos, strength);
}

Vec2
Boid::badWander(Boid& boidToWander,
                const float wanderTime)
{
  if( boidToWander.m_isWandering &&
     boidToWander.m_wanderTime >= wanderTime )
  {
    boidToWander.m_isWandering = false;
    boidToWander.m_wanderTime = 0.0f;
    return Vec2(0.0f, 0.0f);
  }
  else
  {
    boidToWander.m_isWandering = true;
    boidToWander.m_wanderTime = wanderTime;
  }
  return Vec2();
}

Vec2
Boid::evade(const Vec2& currentPos,
            const Boid& pursuer,
            const float predictionTime,
            const float radius,
            const float strength) const
{
  return Vec2();
}

