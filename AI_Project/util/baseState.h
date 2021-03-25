#pragma once
#include "Types.h"
#include "Boid.h"

/**
 * Represents a interface for all
 */
class BaseState
{
public:
 BaseState() = default;
  virtual ~BaseState() = default;

  /**
   * Controls what happens when the boid first enters the state.
   */
  virtual
  void OnEnter(Boid& boid) = 0;

  /**
   * Controls what the boid does every update.
   */
  virtual
  StateType OnUpdate(float deltaTime,Boid& boid) = 0;

  /**
   * What happens when the boid leaves the state.
   */
  virtual
  void OnExit(Boid& boid) = 0;

};
