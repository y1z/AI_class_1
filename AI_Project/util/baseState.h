#pragma once
#include "Types.h"


class BaseState
{
public:

  void virtual OnEnter() = 0;


  State virtual OnUpdate(float deltaTime) = 0;


  void virtual OnExit() = 0;
};
