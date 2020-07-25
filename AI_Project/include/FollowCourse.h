#pragma once
#include "baseState.h"

class FollowCourse :
  public BaseState {
public:
  FollowCourse() = default;
  ~FollowCourse() = default;

  void 
  OnEnter(Boid& boid)override; 

  StateType 
  OnUpdate(float deltaTime,Boid& boid)override;

  void 
  OnExit(Boid& boid) override;
  
};

