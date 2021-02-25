#pragma once
#include "Vec2.h"
#include "IndexTracker.h"

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <cstddef>
#include <deque>
/**
* @file Types.h
* It contains many common types use in the project.
*/

/**
 * FORWARD DECLARATIONS
 */

class Boid;
class Racer;
namespace sf {
  class RenderTarget;
}

/**
 * integer types
 */

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;


/**
 * Types defs
 */
using BoidContainer = std::deque<Boid>;
using RacerContainer = std::deque<Racer>;


/**
 * ENUMS
 */
enum class StateType : uint32
{
  Idle = 0,
  FollowCourse,
  RunOver,

  COUNT
};


/**
 * @brief a individual node of a path.
 */
struct FollowPathNode
{
public:
  FollowPathNode(const Vec2 position, const float radius = 100.0f)
    :m_position(position), m_radius(radius) {}

  Vec2 m_position;
  float m_radius;
};

/**
 * @brief a representation of the path.
 */
struct FollowPath
{
  using PathContainer = std::vector< FollowPathNode >;
  using ShapeContainer = std::vector< sf::CircleShape >;

  ShapeContainer  m_pointsInPath;
  PathContainer  m_pathData;
  sf::VertexArray m_vertexArray;
};

struct LapCount
{
  bool operator <(const LapCount& other) const
  {
    const bool IsALapAhead = m_fullLap < other.m_fullLap;
    const bool IsACheckpointAhead = (m_totalCheckPoint < other.m_totalCheckPoint);
    return IsALapAhead || IsACheckpointAhead;
  }

  bool operator ==(const LapCount& other) const
  {
    const bool sameLaps = (m_fullLap == other.m_fullLap);
    const bool sameCheckPoints = m_totalCheckPoint == other.m_totalCheckPoint;

    return  sameLaps && sameCheckPoints;
  }

  bool operator >(const LapCount& other) const
  {
    const bool isALapBehind = (m_fullLap > other.m_fullLap);
    const bool isACheckpointBehind = m_totalCheckPoint > other.m_totalCheckPoint;
    return isALapBehind || isACheckpointBehind;
  }


  uint32 m_fullLap = 0u;
  uint32 m_totalCheckPoint = 0u;
  uint32 m_currentCheckPoints = 0u;
};


/**
 * @brief controls how a boid will act.
 */
struct BoidDescriptor
{
  BoidDescriptor()
    :m_position(Vec2::zeroVector2),
    m_prevPosition(Vec2::downVector2),
    m_wanderPosition(0.0f, 0.0f),

    m_fleeTargetPosition(nullptr),
    m_seekTargetPosition(nullptr),
    m_arriveTargetPosition(nullptr),
    m_pursueTargetPosition(nullptr),
    m_evadeTargetPosition(nullptr),
    m_boidBeingPursued(nullptr),
    m_boidToEvade(nullptr),
    m_groupOfRacers(nullptr),

    m_color(sf::Color::Blue),

    m_speed(0.0f),
    m_speedMax(125.0f),
    m_acceleration(3.5f),

    m_followPathMagnitude(1.0f),
    m_patrolPathMagnitude(1.0f),
    m_pursueMagnitude(1.0f),
    m_evadeMagnitude(1.0f),
    m_fleeMagnitude(1.0f),
    m_seekMagnitude(1.0f),
    m_arriveMagnitude(1.0f),

    m_purseTimePrediction(0.0f),
    m_evadeTimePrediction(0.0f),

    m_fleeRadius(300.0f),
    m_evadeRadius(300.0f),
    m_arriveRadius(300.0f),

    m_timeInMotion(0.0f),
    m_aggressiveTime(0.0f),
    m_wanderTime(0.0f),
    m_maxForce(3.5f),
    m_mass(0.0005f),
    m_boidSize(30.0f),
    m_state(StateType::Idle),
    m_nodesReached(0u),
    m_isWandering(false),
    m_isFollowingPath(false),
    m_cycleFollowPath(false),
    m_cyclePatrolPath(false)

  {
    m_shape.setRadius(m_boidSize);
    m_shape.setFillColor(m_color);
  }

  /**
  * @brief Used to represent the boid visually on screen.
  */
  sf::CircleShape m_shape;

  /**
  * @brief Container for the boids path.
  */
  std::vector<FollowPathNode> m_pathNodes;

  /**
  * @brief used to keep track of what index the boid is following.
  */
  IndexTracker m_indexTracker;

  // LapCount m_lapCount;

  /**
  * @brief Where the current boid is located.
  */
  Vec2 m_position;


  /**
  * @brief Where the current boid was located and used to determine the
  * direction of the boid.
  */
  Vec2 m_prevPosition;

  /**
  * @brief Used for when the boid needs to wander.
  */
  Vec2 m_wanderPosition;


  /**
  * @brief the position of what the boid is fleeing from.
  */
  const Vec2* m_fleeTargetPosition;

  /**
  * @brief the position of what the boid is seeking.
  */
  const Vec2* m_seekTargetPosition;

  /**
  * @brief the position of what the boid is arriving to.
  */
  const Vec2* m_arriveTargetPosition;

  /**
  * @brief the position of what the boid is pursuing.
  */
  const Vec2* m_pursueTargetPosition;

  /**
  * @brief the position of what the boid is evading from.
  */
  const Vec2* m_evadeTargetPosition;

  /**
  * @brief the boid Being pursued.
  */
  const Boid* m_boidBeingPursued;

  /**
  * @brief the boid Being pursued.
  */
  const Boid* m_boidToEvade;

  /**
  * @brief the pointer to the group of the boid.
  */
  const RacerContainer* m_groupOfRacers;

#if !NDEBUG

  // sf::RenderWindow * m_renderTargetDebug;

#endif // !NDEBUG

  /**
  * @brief The color of the boid.
  */
  sf::Color m_color;

  /**
  * @brief How fast is the boid.
  */
  float m_speed;

  /**
  * @brief How fast is the boid.
  */
  float m_speedMax;

  /**
  * @brief controls the accelerations of the boid.
  */
  float m_acceleration;

  /**
  * @brief Magnitude of the follow-path behavior.
  */
  float m_followPathMagnitude;

  /**
  * @brief Magnitude of the patrol-path behavior.
  */
  float m_patrolPathMagnitude;

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
  * @brief Magnitude of the arrive behavior.
  */
  float m_arriveMagnitude;

  /** @brief controls how far ahead to predict the */
  float m_purseTimePrediction;

  /** @brief controls how far ahead to predict the */
  float m_evadeTimePrediction;

  /**
  * @brief the radius that the used during the flee behavior.
  */
  float m_fleeRadius;

  /** @brief the radius that the used during the flee behavior.*/
  float m_evadeRadius;

  /**
  * @brief the radius use to determine when to slow down in the arrive behavior.
  */
  float m_arriveRadius;

  /**
  * @brief Keeps track of how long the boid has been moving.
  */
  float m_timeInMotion;

  /**
  * @brief how long has a boid been aggressive.
  */
  float m_aggressiveTime;

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
  * @brief keeps track of the state of the boid.
  */
  StateType m_state;

  /**
   * @brief count the amount of nodes reached.
   */
  uint32 m_nodesReached;

  /**
  * @brief keeps track if the boid is wandering.
  */
  bool m_isWandering;

  /**
   * @brief
   */
  bool m_isFollowingPath;

  /**
  * @brief decides if the boid cycles through a path.
  */
  bool m_cycleFollowPath;

  /**
  * @brief decides if the boid cycles through a patrol path.
  */
  bool m_cyclePatrolPath;
};


/** @brief used for initializing the game manager */
struct GameManagerDescriptor
{

  [[nodiscard]] sf::RenderWindow*
  getDebugRenderTarget()
  {

  #if !NDEBUG

    return m_debugRenderTarget;

  #endif // !NDEBUG
    return nullptr;
  }

  void
  setDebugRenderTarget(sf::RenderWindow* renderTarget)
  {
  #if !NDEBUG
    m_debugRenderTarget = renderTarget;
  #endif // !NDEBUG
  };

  /** @brief tell the game manager how each boid behaves. */
  std::vector<BoidDescriptor> m_boidDescriptors;

  /** @brief give the boids a path to use in the game.*/
  std::vector<FollowPathNode> m_pathData;
private:
  sf::RenderWindow* m_debugRenderTarget;

};


