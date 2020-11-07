#include "FSMScoreBord.h"
#include "GameManager.h"

void 
FSMScoreBord::init(UiManager& UI)
{
  GameManager& gm = GameManager::getInstance();
  size_t i = 0u;

  m_positions.resize(gm.getBoidContainerRef().size());
  for(auto& elem : UI )
  {
    elem.m_ptrBoid = &gm.getBoidContainerRef().at(i);
    m_positions.at(i) = elem.getPosition();
    
    ++i;
  }

  m_lapCount.checkPoints = gm.getPathContainerRef().size();
  m_states.push_back(new StateScoreCheck);

}

int 
FSMScoreBord::run(UiManager& UI)
{

  for(auto& elem:  UI )
  {
    m_currentState = m_states[0];
    m_currentState->run(UI, elem, m_lapCount);
  }


 
  return 0;
}
