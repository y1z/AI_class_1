#pragma once
#include "Vec2.h"
#include "Types.h"

/** @file Boid.h
 */

/* FORWARD  DECLARATION*/
namespace sf {
  class RenderTarget;
}

/**@brief Describes an agent that uses steering behaviors.*/
class Boid 
{
public:
  Boid() = default;
  Boid(const Boid & other) = default;
  Boid(Boid && other) noexcept = default;

  explicit Boid(const BoidDescriptor &descriptor);
  explicit Boid(BoidDescriptor &&descriptor);

public: // operators 

 Boid& operator=(const Boid& other) = default;
 Boid& operator=(Boid&& other) noexcept = default;

public: // member functions

  /**
  * @brief Add the force to the current force sum.
  * @param[in] force : The force that will control the boid.
  * @bug no know bugs.
  */
  void
  addForce(const Vec2& force);

  /**
  * @brief Updates the position, forceSum of the boid, should be called every frame.
  * @bug
  */
  void
  update(float deltaTime);
  
  /**
  * @brief Initializes every variable used by the boid.
  * @bug no known bugs.
  */
  void
  init(const BoidDescriptor& descriptor);

  /**
  * @reutrns The direction of the boid.
  */
  Vec2 
  getDir()const;

  /**
  * @brief Set the position the boid will wander to.
  * @param[in] position : Where the boid will wander to.
  * @bug no known bugs.
  */
  void
  setWanderPosition(const Vec2& position );

  /**
  * @brief sets the current state of the boid.
  * @param[in] newState : Where the boid will wander to.
  * @bug no known bugs.
  */
  void
  setStateType(const StateType newState);

  /**
  * @returns The current state.
  */
  StateType
  getStateType()const;

  /**
  * @returns the position where the boid wil wander to.
  * @bug no known bugs.
  */
  Vec2
  getWanderPosition()const;

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
  seek(const Boid& seekerBoid,
       const Boid& targetBoid,
       const float strength = 1.0f) const;

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

  /** Just a redirect to Boid::arrive */
  Vec2
  arrive(const Boid& currentPos,
         const Vec2& destination,
         const float  strength = 1.0f,
         const float  radius = 100.0f)const;

  /**
  * @brief 
  * @bug
  * @param[in] 
  */
  Vec2
  pursue(const Vec2& currentPos,
         const Boid& target,
         const float predictionTime,
         const float strength = 1.0f)const;

  /**
  * @brief Calculates a random position to seek.
  * @param[in] 
  * @bug no known bugs.
  */
  Vec2
  badWander(Boid& boidToWander,
            const float minimumRange,
            const float maximumRange,
            const float wanderTime,
            const float strength = 1.0f)const;

  /**
  * @brief Calculates a vector that attempts to avoid a pursuer.
  * @param[in] pursuer : The agent we are trying to evade.
  * @param[in] predictionTime : Use to determine were the pursuer is going to be
  * in N seconds.
  * @param[in] radius : The minimum Distance before we start evading.
  * @param[in] strength : How strong is the resulting force.
  * @bug no known bugs.
  */
  Vec2
  evade(const Boid& evadeBoid,
        const Boid& pursuer,
        const float predictionTime,
        const float radius = 100.0f,
        const float strength = 1.0f)const;

  /**
  * @brief Calculates a vector that attempts to avoid a pursuer.
  * @param[in] boidToWander : The boid that is going to start wandering.
  * @param[in] inputAngle : The angle in the circle that the boid can wander to.
  * @param[in] circleRadius : The minimum Distance before we start evading.
  * @param[in] PredictionTime : Used to determine how far to make the circle from the boid.
  * @param[in] WanderTime : how long the boid will be wandering.
  * @param[in] strength : How strong is the resulting force.
  * @bug no known bugs.
  */
  Vec2
  wander(Boid& boidToWander,
         const float inputAngle,
         const float circleRadius,
         const float PredictionTime,
         const float WanderTime,
         const float strength = 1.0f)const;

  /**
  * @brief Makes the boid follow a path created a series of nodes.
  * @param[in] pathFollower : The node that is following the path.
  * @param[in] currentNode : Which node is the Boid current going to.
  * @param[in] cyclePath  : Used to know if the boid traverses the path in a cycle.
  * @param[in] strength : The resulting strength of the force.
  * @param[in] path : The path to follow.
  * @bug no known bugs.
  */
  Vec2
  followPath(const Boid& pathFollower,
             IndexTracker& currentNode,
             const std::vector<FollowPathNode>& path,
             const bool cyclePath = false,
             const float strength = 1.0f);

  Vec2
  patrolPath(const Boid& patrolBoid,
             IndexTracker& indexTracker,
             const std::vector<FollowPathNode>& path,
             const bool cyclePath = false,
             const float strength = 1.0f);


public:
  /**
  * @returns A descriptor with all the variables initialized.
  */
  static BoidDescriptor
  createDefaultDescriptor();

  void
  draw(sf::RenderTarget & renderTarget) const;


  void
  destroy();

public:

  /** Contains all the data the boid needs to work.*/
  BoidDescriptor m_data;
};

