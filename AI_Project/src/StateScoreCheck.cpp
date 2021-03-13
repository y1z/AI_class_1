#include "StateScoreCheck.h"


int
StateScoreCheck::run(UiManager& man,
                     UIRectangle& rect,
                     const LapCount& baseLap)
{
  int result = 0;

  const auto sortFunc = [](UIRectangle& rect1, UIRectangle& rect2) {
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
