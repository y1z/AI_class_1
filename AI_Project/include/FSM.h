#pragma once
#include "baseState.h"
#include "Types.h"
#include <array>

/**
* @brief contains a series of state each boid can execute
*/
class FSM 
{
public:
  FSM();
  ~FSM();

  
public:

  int 
  run(const float deltaTime);

private:
  std::array<BaseState*, static_cast< size_t >(StateType::COUNT) >m_states;
};

