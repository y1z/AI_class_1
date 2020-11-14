#include "StateScoreCheck.h"
int
StateScoreCheck::run(UiManager& man,
                     UiRectangle& rect,
                     const LapCount& baseLap)
{
  int result = 0;

  if( rect.m_ptrBoid->m_data.m_lapCount.m_currentCheckPoints >= baseLap.m_currentCheckPoints )
  {
    rect.m_ptrBoid->m_data.m_lapCount.m_fullLap += 1;
    rect.m_ptrBoid->m_data.m_lapCount.m_currentCheckPoints = 0;
  }
  const auto sortFunc = [](UiRectangle& rect1, UiRectangle& rect2) {
    const bool shouldSwap = (rect1 < rect2);
    //if( shouldSwap )
    //{
    //  rect1.swapPosition(rect2);
    //}
    return shouldSwap;
  };

  std::sort(man.begin(), man.end(), sortFunc);

  return result;
}
