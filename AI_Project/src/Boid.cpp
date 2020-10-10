#include "Boid.h"
#include "util.h"

#include "SFML/Graphics/RenderTarget.hpp"

#include <utility>

Boid::Boid(const BoidDescriptor& descriptor)
  :m_data(descriptor)
{
   m_data.m_shape.setFillColor(m_data.m_color);
}

Boid::Boid(BoidDescriptor&& descriptor)
  : m_data(std::forward<BoidDescriptor>( descriptor))
{
   m_data.m_shape.setFillColor(m_data.m_color);
}

void
Boid::update(float deltaTime)
{
  Vec2 force = Vec2::zeroVector2;

  if( nullptr != m_data.m_seekTargetPosition )
    force += this->seek(m_data.m_position, *m_data.m_seekTargetPosition, m_data.m_seekMagnitude);

  if( nullptr != m_data.m_fleeTargetPosition )
    force += this->flee(m_data.m_position, *m_data.m_fleeTargetPosition, m_data.m_fleeMagnitude, m_data.m_fleeRadius);

  if( nullptr != m_data.m_boidBeingPursued )
    force += this->pursue(m_data.m_position, *m_data.m_boidBeingPursued, m_data.m_purseTimePrediction, m_data.m_pursueMagnitude);

  if( nullptr != m_data.m_boidToEvade )
    force += this->evade(*this, *m_data.m_boidToEvade, m_data.m_evadeTimePrediction, m_data.m_evadeRadius, m_data.m_evadeMagnitude);

  if( !m_data.m_pathNodes.empty() && m_data.m_isFollowingPath )
    force += this->followPath(*this, m_data.m_indexTracker, m_data.m_pathNodes, m_data.m_cycleFollowPath, m_data.m_followPathMagnitude);

  if( !m_data.m_pathNodes.empty() && !m_data.m_isFollowingPath )
    force += this->patrolPath(*this, m_data.m_indexTracker, m_data.m_pathNodes, m_data.m_cyclePatrolPath, m_data.m_patrolPathMagnitude);

  if( force.length() > std::numeric_limits<float>::epsilon() )
  {
    m_data.m_timeInMotion += deltaTime;
  }
  else
  {
    m_data.m_timeInMotion = 0.0f;
  }

  m_data.m_speed = (m_data.m_timeInMotion * m_data.m_timeInMotion) * m_data.m_acceleration;
  if( m_data.m_speed > m_data.m_speedMax )
  {
    m_data.m_speed = m_data.m_speedMax;
  }

  Vec2 const Dir = getDir();
  Vec2 const SteerDir = ((force * m_data.m_mass).normalize() - Dir).normalize();
  Vec2 const ResultDir = (SteerDir + Dir);

  Vec2 const TempPrevPosition = m_data.m_position;

  m_data.m_position += (ResultDir) * (m_data.m_speed * deltaTime);
  m_data.m_shape.setPosition(m_data.m_position.x, m_data.m_position.y);

  if( TempPrevPosition.notEquals(m_data.m_position, 7) )
  {
    m_data.m_prevPosition = TempPrevPosition;
  }

  if( m_data.m_isWandering )
  {
    m_data.m_wanderTime += deltaTime;
  }
}

void
Boid::init(const BoidDescriptor& descriptor)
{
  m_data = descriptor;
  m_data.m_shape.setFillColor(m_data.m_color);
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

void
Boid::setStateType(const StateType newState)
{
  m_data.m_state = newState;
}

StateType
Boid::getStateType() const
{
  return m_data.m_state;
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
    return this->seek(currentPos, positionToFleeFrom, strength) * -1;
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
             const float strength) const
{
  Vec2 const projectedRadius = target.getDir() * (target.m_data.m_speed * predictionTime);

  Vec2 const projectPos = target.m_data.m_position + projectedRadius;

  Vec2 const distanceFromTarget = target.m_data.m_position - currentPos;

  Vec2 const distanceFromProjection = projectPos - currentPos;

  const float projectionMagnitude = distanceFromProjection.lengthSqr();

  const float magnitudeFromTarget = distanceFromTarget.lengthSqr();

  if( projectionMagnitude < magnitudeFromTarget )
  {
    const float radiusReduction = projectionMagnitude / magnitudeFromTarget;
    return this->seek(currentPos, projectPos + (projectedRadius * radiusReduction), strength);
  }
  else
    return this->seek(currentPos, projectPos, strength);
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
    boidToWander.setWanderPosition(Vec2(0.0f, 0.0f));
  }

  return Vec2(0.f);
}


Vec2
Boid::followPath(const Boid& pathFollower,
                 IndexTracker& indexTracker,
                 const std::vector<FollowPathNode>& path,
                 const bool cyclePath,
                 const float strength)
{
  const FollowPathNode* nextNode = &path.at(indexTracker.getCurrentIndex());

  const float distanceSquared = (nextNode->m_position - pathFollower.m_data.m_position).lengthSqr();

  if( distanceSquared <= nextNode->m_radius * nextNode->m_radius )
  {
    const auto currentIndex = indexTracker.getCurrentIndex();
    if( cyclePath )
    {
      indexTracker.setCurrentIndex((currentIndex + 1) % path.size());
    }
    else if( currentIndex + 1 <= path.size() - 1 )
    {
      indexTracker.incrementIndex();
    }
    nextNode = &path.at(indexTracker.getCurrentIndex());
  }

  if( 0u == indexTracker.getCurrentIndex() )
  {
    return seek(pathFollower.m_data.m_position,
                path[indexTracker.getCurrentIndex()].m_position,
                strength);
  }

  auto const previousNode = (indexTracker.getIncrementAmount() * -1);

  const FollowPathNode* const prevNode = &path.at(indexTracker.getCurrentIndex() + previousNode);

  const Vec2 pathToNextNode = nextNode->m_position - prevNode->m_position;
  const Vec2 pathToBoid = pathFollower.m_data.m_position - prevNode->m_position;

  const Vec2 pointOnTheLine = pathToBoid.projectOnTo(pathToNextNode) + prevNode->m_position;

  return seek(pathFollower.m_data.m_position, pointOnTheLine, strength) +
    seek(pathFollower.m_data.m_position, nextNode->m_position, strength);
}

Vec2
Boid::patrolPath(const Boid& patrolBoid,
                 IndexTracker& indexTracker,
                 const std::vector<FollowPathNode>& path,
                 const bool cyclePath,
                 const float strength)
{
  const FollowPathNode* nextNode = &path.at(indexTracker.getCurrentIndex());

  const float distanceSquared = nextNode->m_position.distanceFromVectorSqr(patrolBoid.m_data.m_position);

  if( distanceSquared < nextNode->m_position * nextNode->m_position )
  {
    auto const currentIndex = indexTracker.getCurrentIndex();
    if( 1 > currentIndex )
    {
      indexTracker.setIncrementAmount(1);
    }
    else if( path.size() - 1 == currentIndex )
    {
      indexTracker.setIncrementAmount(-1);
    }

    indexTracker.incrementIndex();

  }

  auto const previousNode = (indexTracker.getIncrementAmount() * -1);

  if( previousNode < 0 )
  {
    return this->seek(patrolBoid.m_data.m_position, nextNode->m_position, strength);
  }



  const FollowPathNode* prevNode = &path.at(indexTracker.getCurrentIndex() + previousNode);

  const Vec2 pathToNextNode = nextNode->m_position - prevNode->m_position;
  const Vec2 pathToBoid = patrolBoid.m_data.m_position - prevNode->m_position;

  const Vec2 pointOnTheLine = pathToBoid.projectOnTo(pathToNextNode) + prevNode->m_position;

  return seek(patrolBoid.m_data.m_position, pointOnTheLine, strength) +
    seek(patrolBoid.m_data.m_position, nextNode->m_position, strength);
}

void
Boid::draw(sf::RenderTarget& renderTarget) const
{
  renderTarget.draw(m_data.m_shape);
}

void 
Boid::destroy()
{
  m_data.m_seekTargetPosition = nullptr;
  m_data.m_fleeTargetPosition = nullptr;
  m_data.m_evadeTargetPosition = nullptr;
  m_data.m_pursueTargetPosition = nullptr;
  m_data.m_arriveTargetPosition = nullptr;
  m_data.m_boidBeingPursued = nullptr;
  m_data.m_boidToEvade = nullptr;
  m_data.m_wanderPosition = Vec2::minVector2;
  

  m_data.m_pathNodes.clear();
  m_data.m_pathNodes.shrink_to_fit();
  m_data.m_shape.setPosition(Vec2::minVector2.x, Vec2::minVector2.y);
  m_data.m_shape.setFillColor(sf::Color::Transparent);

}

BoidDescriptor 
Boid::createSeekingBoidDescriptor(const Vec2& targetPosition,
                                  const Vec2 boidPosition,
                                  const float forceMagnitude)
{
  BoidDescriptor result;
  result.m_seekTargetPosition = &targetPosition;
  result.m_position = boidPosition;
  result.m_seekMagnitude = forceMagnitude;

  result.m_color = sf::Color::White;
  return result;
}

BoidDescriptor
Boid::createFleeBoidDescriptor(const Vec2& targetPosition,
                                  const Vec2 boidPosition,
                                  const float forceMagnitude,
                                  const float fleeRadius)
{
  BoidDescriptor result;
  result.m_fleeTargetPosition = &targetPosition;
  result.m_position = boidPosition;
  result.m_fleeMagnitude = forceMagnitude;
  result.m_fleeRadius = fleeRadius;

  result.m_color = sf::Color::Yellow;
  return result;
}

BoidDescriptor
Boid::createArrivingBoidDescriptor(const Vec2& targetPosition,
                                   const Vec2 boidPosition,
                                   const float forceMagnitude,
                                   const float arriveRadius)
{
  BoidDescriptor result;
  result.m_arriveTargetPosition = &targetPosition;
  result.m_position = boidPosition;
  result.m_arriveMagnitude = forceMagnitude;
  result.m_arriveRadius = arriveRadius;

  result.m_color = sf::Color::Magenta;
  return result;
}


BoidDescriptor 
Boid::createPursueBoidDescriptor(const Boid& pursueBoid,
                                 const Vec2 boidPosition,
                                 const float forceMagnitude,
                                 const float predictionTime)
{
  BoidDescriptor result;
  result.m_boidBeingPursued = &pursueBoid;
  result.m_position = boidPosition;
  result.m_pursueMagnitude = forceMagnitude;
  result.m_purseTimePrediction = predictionTime;
  result.m_color = sf::Color::Red;
  return result;
}

BoidDescriptor 
Boid::createFollowPathBoidDescriptor(const std::vector<FollowPathNode>& path,
                                     const Vec2& boidPosition,
                                     const float forceMagnitude)
{
  BoidDescriptor result;
  result.m_pathNodes = path;
  result.m_position = boidPosition;
  result.m_followPathMagnitude = forceMagnitude;
  result.m_isFollowingPath = true;
  return result;
}


