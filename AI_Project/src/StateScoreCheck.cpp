#include "StateScoreCheck.h"
int 
StateScoreCheck::run(UiManager& man,
                     UiRectangle& rect,
                     const LapCount& baseLap)
{
  int result = 0;

  if( rect.m_ptrBoid->m_data.m_lapCount.checkPoints >= baseLap.checkPoints )
  {
    rect.m_ptrBoid->m_data.m_lapCount.m_fullLap += 1;
  }
 auto sortFunc =[](UiRectangle& rect1 ,UiRectangle& rect2 )
 {
   const bool result = (rect1 < rect2);
   if( result )
   {
     rect1.SwapPosition(rect2);
   }
   return result;
 };

 std::sort(man.begin(), man.end(), sortFunc);

  return result;
}
