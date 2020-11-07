#pragma once
#include "StateScoreBase.h"
class StateScoreCheck : public StateScoreBase  
{
public:
  int
  run(UiManager& man,
      UiRectangle& rect,
      const LapCount& baseLap) override;

};

