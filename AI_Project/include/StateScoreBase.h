#pragma once
#include "Types.h"
#include "UiManager.h"



/**
 * @file
 * @class StateScoreBase : represents a state of the scoreboard.
 */
class StateScoreBase 
{
public:
  StateScoreBase() = default;
  StateScoreBase(const StateScoreBase&) = default;
  StateScoreBase(StateScoreBase&&)noexcept = default;
  virtual ~StateScoreBase() = default;
public:
  StateScoreBase& operator= (const StateScoreBase&) = default;
  StateScoreBase& operator= (StateScoreBase&&)noexcept = default;
public:
  virtual int
  run(UiManager& man ,UIRectangle& rect, const LapCount& baseLap) = 0;
  
};
