#pragma once
#include "baseState.h"

/**
 * Represents what happens to a boid on the idle state.
 */
class IdleState : public BaseState
{
public:
  IdleState() = default;
  ~IdleState() = default;

  /**
   * @see BaseState::OnEnter()
   */
  void
  OnEnter(Boid& boid) override;

  /**
   * @see BaseState::OnUpdate()
   */
  StateType
  OnUpdate(float deltaTime,Boid& boid)override;

  /**
   * @see BaseState::OnExit();
   */
  void
  OnExit(Boid& boid) override;
};

