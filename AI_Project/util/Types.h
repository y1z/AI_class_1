#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>
/**
* @file Types.h
* It contains many common types use in the project.
*/

/**
 * ENUMS 
 */
enum class BoidBehavior
{
  Seek =  1 << 0,
  Flee =  1 << 1,
  Pursue = 1 << 2,
  Evade =  1 << 3,


  ALL_BEHAVIORS = Seek | Flee | Pursue | Evade ,

  COUNT,
};

struct FollowPathNode
{
  Vec2 m_position;
  float m_radius;
};

struct BoidDescriptor
{
  /**
  * @brief Used to represent the boid visually on screen.
  */
  sf::CircleShape m_shape;

  /**
  * @brief Where the current boid is located.
  */
  Vec2 m_position;

  /**
  * @brief The collective sum of all forces applied to the boid.
  */
  Vec2 m_forceSum;

  /**
  * @brief Where the current boid was located and used to determine the
  * direction of the boid.
  */
  Vec2 m_prevPosition;

  /**
  * @brief the position of what the boid is pursuing.
  */
  Vec2 m_pursueTargetPosition;

  /**
  * @brief the position of what the boid is evading from.
  */
  Vec2 m_evadeTargetPosition;

  /**
  * @brief the position of what the boid is fleeing from.
  */
  Vec2 m_fleeTargetPosition;

  /**
  * @brief the position of what the boid is seeking.
  */
  Vec2 m_seekTargetPosition;

  /**
  * @brief Used for when the boid needs to wander.
  */
  Vec2 m_wanderPosition;

  /**
  * @brief The color of the boid.
  */
  sf::Color m_color;

  /**
  * @brief How fast is the boid.
  */
  float m_speed;

  /**
  * @brief controls the accelerations of the boid.
  */
  float m_acceleration;

  /**
  * @brief Magnitude of the pursue behavior.
  */
  float m_pursueMagnitude;

  /**
  * @brief Magnitude of the evade behavior.
  */
  float m_evadeMagnitude;

  /**
  * @brief Magnitude of the flee behavior.
  */
  float m_fleeMagnitude;

  /**
  * @brief Magnitude of the seek behavior.
  */
  float m_seekMagnitude;

  /**
  * @brief Keeps track of how long the boid has been moving.
  */
  float m_timeInMotion;

  /**
  * @brief How much time the boid has been wandering.
  */
  float m_wanderTime;

  /**
  * @brief The maximum force the boid can use.
  */
  float m_maxForce;

  /**
  * @brief How much mass does the boid have.
  */
  float m_mass;

  /**
  * @brief : controls how big the boid is.
  */
  float m_boidSize;

  /**
  * @brief keeps track if the boid is wandering.
  */
  bool m_isWandering;
};

