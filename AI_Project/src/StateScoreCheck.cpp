#include "StateScoreCheck.h"


int
StateScoreCheck::run(UiManager& man,
                     UiRectangle& rect,
                     const LapCount& baseLap)
{
  int result = 0;

  const auto sortFunc = [](UiRectangle& rect1, UiRectangle& rect2) {
    const bool shouldSwap = (rect1 < rect2);
    if( shouldSwap )
    {
      rect1.swapPosition(rect2);
    }
    return shouldSwap;
  };

  std::sort(man.begin(), man.end(), sortFunc);

  return result;
}
