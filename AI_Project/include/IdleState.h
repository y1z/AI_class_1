#pragma once
#include "baseState.h"

class IdleState : public BaseState 
{
public:
  IdleState() = default;
  ~IdleState() = default;

  void 
  OnEnter(Boid& boid) override;


  StateType 
  OnUpdate(float deltaTime,Boid& boid)override;


  void 
  OnExit(Boid& boid) override;
};

