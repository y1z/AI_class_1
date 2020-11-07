#pragma once
#include "Types.h"
#include "UiManager.h"


class StateScoreBase 
{
public:
  virtual int
  run(UiManager& man ,UiRectangle& rect, const LapCount& baseLap) = 0;
  
};
