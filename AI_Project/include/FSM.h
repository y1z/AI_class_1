#pragma once
#include "baseState.h"
#include "Types.h"
#include <array>
#include <type_traits>

/**
* @brief contains a series of state each boid can execute
*/
class FSM
{
public:
  using enumIndex = std::underlying_type_t< StateType>;
public:
  FSM();
  ~FSM();


public:

  int
  run(const float deltaTime);

private:
  std::array<BaseState*, static_cast< size_t >(StateType::COUNT) >m_states;
};

