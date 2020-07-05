#include "Boid.h"
#include "util.h"
#include "Types.h"

Boid::Boid(const BoidDescriptor& descriptor)
:m_data(descriptor)
{
  m_data.m_shape.setFillColor(sf::Color::Blue);
}

Boid::Boid(BoidDescriptor&& descriptor)
  :m_data(descriptor)
{
  m_data.m_shape.setFillColor(sf::Color::Blue);
}

void
Boid::addForce(const Vec2& force)
{
  m_data.m_forceSum += force;
}

void
Boid::update(float deltaTime)
{
  Vec2 force = Vec2::zeroVector2;

  force += this->seek(m_data.m_position, m_data.m_seekTargetPosition, m_data.m_seekMagnitude);
  force += this->flee();

  Vec2 const Dir = getDir();
  Vec2 const SteerDir = (m_data.m_forceSum - Dir).normalize();
  Vec2 const ResultDir = (SteerDir + Dir);

  m_data.m_position += ResultDir.normalize() * (m_data.m_speed * deltaTime);

  Vec2 const TempPrevPosition = m_data.m_position;
  if( TempPrevPosition != m_data.m_position )
  {
    m_data.m_prevPosition = TempPrevPosition;
  }

  m_data.m_shape.setPosition(m_data.m_position.x, m_data.m_position.y);

  if( m_data.m_forceSum.lengthSqr() > m_data.m_maxForce * m_data.m_maxForce )
  {
    m_data.m_forceSum.normalize() *= m_data.m_maxForce;
  }

  if(this->m_data.m_isWandering )
  {
    m_data.m_wanderTime += deltaTime;
  }
}

void 
Boid::init(const BoidDescriptor& descriptor)
{
  m_data = descriptor;

  m_data.m_shape.setFillColor(sf::Color::Blue);
}

Vec2
Boid::getDir() const
{
  return (m_data.m_position - m_data.m_prevPosition).normalize();
}

void
Boid::setWanderPosition(const Vec2& position)
{
  m_data.m_wanderPosition = position;
}

Vec2
Boid::getWanderPosition() const
{
  return m_data.m_wanderPosition;
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
  return this->seek(seekerBoid.m_data.m_position, targetBoid.m_data.m_position, strength);
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
             const float strength,
             const float radius) const
{
  Vec2 const distanceToDestination = destination - currentPos;
  const float distance = distanceToDestination.magnitude();

  if( distance < radius )
  {
    const float  inverseRadius = 1.0f / radius;
    const Vec2 result = this->seek(currentPos, destination, strength) * (inverseRadius * distance);
    return result;
  }

  return this->seek(currentPos, destination, strength);
}

Vec2
Boid::arrive(const Boid& currentPos,
             const Vec2& destination,
             const float strength,
             const float radius) const
{
  return this->arrive(currentPos.m_data.m_position,
                      destination,
                      strength,
                      radius);
}

Vec2
Boid::pursue(const Vec2& currentPos,
             const Boid& target,
             const float predictionTime,
             const float strength)const
{
  Vec2 const projectedRadius = target.getDir() * target.m_data.m_speed * predictionTime;

  Vec2 const projectPos = target.m_data.m_position + projectedRadius;

  Vec2 const distanceFromTarget = target.m_data.m_position - currentPos;

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
                const float minimumRange,
                const float maximumRange,
                const float wanderTime,
                const float strength)const
{
  if( boidToWander.m_data.m_isWandering &&
     boidToWander.m_data.m_wanderTime >= wanderTime )
  {
    boidToWander.m_data.m_isWandering = false;
    boidToWander.m_data.m_wanderTime = 0.0f;
    return Vec2(0.0f, 0.0f);
  }
  else if( !boidToWander.m_data.m_isWandering )
  {
    boidToWander.m_data.m_isWandering = true;
    Vec2 const position = Vec2(util::randomRangeFloat(minimumRange, maximumRange),
                               util::randomRangeFloat(minimumRange, maximumRange));

    boidToWander.setWanderPosition(position);
    return seek(boidToWander.m_data.m_position, position + boidToWander.m_data.m_position, strength);
  }
  else
  {
    return seek(boidToWander.m_data.m_position,
                boidToWander.getWanderPosition() + boidToWander.m_data.m_position,
                strength);
  }

}


Vec2
Boid::evade(const Boid& evaderBoid,
            const Boid& pursuer,
            const float predictionTime,
            const float radius,
            const float strength) const
{
  Vec2 const projectedRadius = pursuer.getDir() * (pursuer.m_data.m_speed * predictionTime);

  Vec2 const projectedPosition = projectedRadius + pursuer.m_data.m_position;

  Vec2 const distanceFromPursuer = evaderBoid.m_data.m_position - pursuer.m_data.m_position;

  if( distanceFromPursuer.lengthSqr() < projectedRadius.lengthSqr() )
  {
    Vec2 const FleeFromThis = distanceFromPursuer.perpendicularClockWise() + evaderBoid.m_data.m_position;;

    return flee(evaderBoid.m_data.m_position, FleeFromThis, strength, radius);
  }
  else
  {
    return flee(evaderBoid.m_data.m_position, projectedPosition, strength, radius);
  }

  return Vec2();
}

Vec2
Boid::wander(Boid& boidToWander,
             const float inputAngle,
             const float circleRadius,
             const float PredictionTime,
             const float WanderTime,
             const float strength) const
{

  if( !boidToWander.m_data.m_isWandering )
  {
    const float percentageChange = util::randomRangeFloat(-0.5f, 0.5f);

    const float changeInAngle = (percentageChange * inputAngle); 

    Vec2 const currentDirection = boidToWander.getDir();

    Vec2 const futurePosition = boidToWander.m_data.m_position + (currentDirection * boidToWander.m_data.m_speed * PredictionTime);

    Vec2 const positionInCirclePerimeter = currentDirection * circleRadius;

    Vec2 const finalPosition = futurePosition + (positionInCirclePerimeter.rotate(changeInAngle));

    boidToWander.setWanderPosition(finalPosition);
    boidToWander.m_data.m_wanderTime = 0.0f;
    boidToWander.m_data.m_isWandering = true;

    return  seek(boidToWander.m_data.m_position, finalPosition, strength);
  }
  else if( boidToWander.m_data.m_isWandering &&
          boidToWander.m_data.m_wanderTime < WanderTime )
  {
    return  seek(boidToWander.m_data.m_position,
                 boidToWander.getWanderPosition(),
                 strength);
  }
  else
  {
    boidToWander.m_data.m_isWandering = false;
    boidToWander.m_data.m_wanderTime = 0.0f;
    boidToWander.setWanderPosition(Vec2(0.0f,0.0f));
  }

  return Vec2(0.f);
}

Vec2
Boid::followPath(const Boid& pathFollower,
                 std::size_t& currentNode,
                 const std::vector<FollowPathNode>& path,
                 const bool cyclePath,
                 const float strength)
{

  const FollowPathNode* nextNode = &path.at(currentNode);

  const float distanceSquared = (nextNode->m_position - pathFollower.m_data.m_position).lengthSqr();
  if( distanceSquared <= nextNode->m_radius * nextNode->m_radius )
  {
    if( cyclePath )
    {
      currentNode = (currentNode + 1) % path.size();
    }
    else if( currentNode + 1 <= path.size() - 1 )
    {
      ++currentNode;
    }
    nextNode = &path.at(currentNode);
  }

  if( 0u == currentNode )
  {
    return seek(pathFollower.m_data.m_position,
                path[currentNode].m_position,
                strength);
  }

  const FollowPathNode* prevNode = &path.at(currentNode - 1);

  const Vec2 pathToNextNode = nextNode->m_position - prevNode->m_position;
  const Vec2 pathToBoid = pathFollower.m_data.m_position - prevNode->m_position;

  const Vec2 pointOnTheLine = pathToBoid.projectOnTo(pathToNextNode) + prevNode->m_position;

 return seek(pathFollower.m_data.m_position,pointOnTheLine, strength) + 
  seek(pathFollower.m_data.m_position, nextNode->m_position, strength);
}

BoidDescriptor 
Boid::createDefaultDescriptor()
{
  BoidDescriptor result;

  result.m_boidSize = 30.0f;
  result.m_color = sf::Color::Blue;
  result.m_shape.setRadius(result.m_boidSize);
  result.m_shape.setFillColor(result.m_color);

  result.m_position = Vec2::zeroVector2;
  result.m_prevPosition = Vec2::downVector2;
  result.m_seekTargetPosition = Vec2::zeroVector2;
  result.m_fleeTargetPosition = Vec2::zeroVector2;
  result.m_evadeTargetPosition = Vec2::zeroVector2;
  result.m_pursueTargetPosition = Vec2::zeroVector2;
  result.m_wanderPosition = Vec2::zeroVector2;

  result.m_forceSum = Vec2::zeroVector2;

  result.m_seekMagnitude = 1.0f;
  result.m_fleeMagnitude = 0.0f;
  result.m_pursueMagnitude = 0.0f;
  result.m_evadeMagnitude = 0.0f;

  result.m_acceleration = 1.5f;
  result.m_speed = 5.0f;
  result.m_wanderTime = 0.0f;
  result.m_timeInMotion = 0.0f;
  result.m_mass = 0.5f;
  result.m_maxForce = 2.0f;

  return result;
}


