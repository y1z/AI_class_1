#pragma once
#include "Boid.h"
#include "Vec2.h"
#include <cstdint>
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

};


/**
 * STRUCTS
 */
struct BoidAndBehavior
{
  Boid m_boid;
  BoidBehavior m_behavior;
};

struct FollowPathNode
{
  Vec2 m_position;
  float m_radius;
};


