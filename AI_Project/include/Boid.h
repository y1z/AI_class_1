#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>
/** @file Boid.h
 * @brief Describes an agent that uses steering behaviors.
 */

class Boid
{
public:
  Boid() = default;
  Boid(const Boid & other) = default;
  Boid(Boid && other) noexcept = default;

  explicit Boid(const Vec2 & position);
public: // operators 
 Boid& operator=(const Boid& other) = default;
 Boid& operator=(Boid&& other) noexcept = default;
public: // member functions
  /**
  * @brief Initializes the boid.
  * @bug
  */
  void
  init(Vec2 const &position, 
       const float speed = 10.0f,
       const float radius = 100.0f,
       const sf::Color boidColor = sf::Color::Blue);

  /**
  * @reutrns The direction of the boid.
  */
  Vec2 
  getDir()const;

  /**
  * @returns A vector that goes to the positionToFleeFrom
  * @param[in] currentPos : Where we are in the world.
  * @param[in] targetBoid : The position where we are going.
  * @param[in] strength : Controls the magnitude of the vector.
  * @bug no known bugs.
  * @note every overload of this function just redirects to this one.
  */
  Vec2 
  seek(const Vec2& currentPos,
       const Vec2& destination,
       const float  strength = 1.0f) const;

  /** Just a redirect to Boid::seek */
  Vec2 
  seek(const Boid& someBoid,
       const Boid& targetBoid,
       const float  strength = 1.0f) const;

  /**
  * @returns A vector that flees from a position.
  * @param[in] strength controls the length of the vector.
  * @param[in] currentPos : Where we are in the world.
  * @param[in] positionToFleeFrom : The position we are getting away from.
  * @param[in] radius : How close the other agent can be before we start fleeing.
  * @bug no known bugs.
  */
  Vec2
  flee(const Vec2& currentPos,
       const Vec2& positionToFleeFrom,
       const float  strength = 1.0f,
       const float  radius = 100.0f)const;

  /**
  * @brief Seeks a target at full speed until it gets close enough ( determined by a
  * radius ) it slows down.
  * @param[in] 
  * @bug no known bugs.
  */
  Vec2
  arrive(const Vec2& currentPos,
         const Vec2& destination,
         const float  strength = 1.0f,
         const float  radius = 100.0f)const;

  Vec2
  pursue(const Vec2& currentPos,
         const Boid& target,
         const float predictionTime,
         const float strength = 1.0f)const;

  Vec2
  badWander(Boid& boidToWander,
            const float wanderTime);

  /**
  * @brief Calculates a vector that attempts to avoid a pursuer.
  * @param[in] currentPos : The current position of the evader.
  * @param[in] pursuer : The agent we are trying to evade.
  * @param[in] predictionTime : Use to determine were the pursuer is going to be
  * in N seconds.
  * @param[in] radius : The minimum Distance before we start evading.
  * @param[in] strength : How strong is the resulting force.
  * @bug no known bugs.
  */
  Vec2
  evade(const Vec2& currentPos,
        const Boid& pursuer,
        const float predictionTime,
        const float radius = 100.0f,
        const float strength = 1.0f)const;
public:

  sf::CircleShape m_shape;
  /**
  * @brief Where the current boid is located.
  */
  Vec2 m_position;
private:

  /**
  * @brief Where the current boid was located and used to determine the 
  * direction of the boid.
  */
  Vec2 m_prevPosition;
public:

  /**
  * @brief How fast is the boid.
  */
  float m_speed;
private:

  /**
  * @brief How much time the boid has been wandering.
  */
  float m_wanderTime;

  /**
  * @brief keeps track if the boid is wandering.
  */
  bool m_isWandering;

};

