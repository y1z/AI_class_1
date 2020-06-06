#pragma once
#include "Vec2.h"

class Boid
{
public:
  Boid() = default;
  Boid(const Boid& other) = default;
  Boid(Boid&& other) noexcept = default;

  Boid(const Vec2&position);
public: // member functions

  Vec2 
  getDir()const;

  /**
  * @returns A vector that goes to the positionToFleeFrom
  * @param[in] currentPos : Where we are in the world.
  * @param[in] destination : The position where we are going.
  * @param[in] strength : Controls the magnitude of the vector.
  * @bug no known bugs.
  */
  Vec2 
  seek(Vec2 const& currentPos,
       Vec2 const& destination,
       float const strength = 1.0f) const;

  /**
  * @returns A vector that flees from a position.
  * @param[in] strength controls the length of the vector.
  * @param[in] currentPos : Where we are in the world.
  * @param[in] positionToFleeFrom : The position we are getting away from.
  * @bug no known bugs.
  */
  Vec2
  flee(Vec2 const& currentPos,
       Vec2 const& positionToFleeFrom,
       float const strength = 1.0f,
       float const radius = 100.0f)const;


  Vec2
  arrive(Vec2 const& currentPos,
         Vec2 const& destination,
         float const strength = 1.0f,
         float const radius = 100.0f)const;

  Vec2
  pursue(Vec2 const& currentPos,
         Boid const& target,
         const float deltaTime,
         float const strength = 1.0f)const;
public:

  Vec2 m_position;
private:

  Vec2 m_prevPosition;
public:
  float m_speed;

};

