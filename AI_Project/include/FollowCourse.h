#pragma once
#include "baseState.h"

/**
 * Controls the boid when they are supposed to follow the course
 */
class FollowCourseState : public BaseState
{
public:
  FollowCourseState() = default;
  ~FollowCourseState() = default;

  /**
   * @see BaseState::OnEnter();
   */
  void
  OnEnter(Boid& boid)override;

  /**
   * Makes the boid follow the course util other boid get too close then
   * the boid becomes aggressive .
   */
  StateType
  OnUpdate(float deltaTime,Boid& boid)override;

  /**
   * @see BaseState::OnExit();
   */
  void
  OnExit(Boid& boid) override;

};

