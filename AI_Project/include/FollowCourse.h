#pragma once
#include "baseState.h"

class FollowCourseState : public BaseState 
{
public:
  FollowCourseState() = default;
  ~FollowCourseState() = default;

  void 
  OnEnter(Boid& boid)override; 

  StateType 
  OnUpdate(float deltaTime,Boid& boid)override;

  void 
  OnExit(Boid& boid) override;
  
};

