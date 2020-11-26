#pragma once
#include "Types.h"
#include "Boid.h"
#include "Racer.h"

class BaseState
{
public:
 BaseState() = default;
  virtual ~BaseState() = default;

  
  virtual 
  void OnEnter(Boid& boid) = 0;

  virtual 
  StateType OnUpdate(float deltaTime,Boid& boid) = 0;

  virtual
  void OnExit(Boid& boid) = 0;

};
