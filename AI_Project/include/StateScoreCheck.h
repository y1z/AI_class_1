#pragma once
#include "StateScoreBase.h"

/**
 * @file
 * @class StateScoreCheck : represents the score board checking that the position of the 
 * UiRectangle are in their correct position relative to the racers.
 */
class StateScoreCheck : public StateScoreBase  
{
public:
  int
  run(UiManager& man,
      UiRectangle& rect,
      const LapCount& baseLap) override;

};

