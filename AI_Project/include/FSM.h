#pragma once
#include  "baseState.h"
#include  "Types.h"
#include <array>

class FSM 
{
public:
  FSM();
  ~FSM();

  

  
  int 
  run();

  std::array<BaseState*, (size_t)StateType::COUNT >m_states;
};

