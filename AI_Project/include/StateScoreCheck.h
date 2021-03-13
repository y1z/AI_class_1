#pragma once
#include "StateScoreBase.h"

/**
 * @file
 * @class StateScoreCheck : represents the score board checking that the position of the 
 * UIRectangle are in their correct position relative to the racers.
 */
class StateScoreCheck : public StateScoreBase  
{
public:
  int
  run(UiManager& man,
      UIRectangle& rect,
      const LapCount& baseLap) override;

};

