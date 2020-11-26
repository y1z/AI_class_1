#include "FSMScoreBord.h"
#include "GameManager.h"
#include "StateScoreCheck.h"
#include <cassert>

FSMScoreBord::FSMScoreBord()
{
  m_states.reserve(4);
  m_states.push_back(new StateScoreCheck);
}

//board
FSMScoreBord::~FSMScoreBord()
{
  for(auto& state : m_states )
  {
    if( nullptr != state )
    {
      delete state;
    }
  }
  
}

void
FSMScoreBord::init(UiManager& UI)
{
  GameManager& gm = GameManager::getInstance();
  size_t i = 0u;

  for(auto& elem : UI )
  {
    elem.m_ptrRacer = &gm.getAgentContainerRef().at(i);
    
    ++i;
  }

  m_currentLapCount.m_currentCheckPoints = gm.getPathContainerRef().size();

}

int 
FSMScoreBord::run(UiManager& UI)
{

  for(auto& elem:  UI )
  {
    m_currentState = m_states[0];
    if( nullptr != m_currentState )
    {
      m_currentState->run(UI, elem, m_currentLapCount);
    }
    else
    {
      assert( nullptr != m_currentState && "State pointer is pointing to null, check container");
    }
  }
 
  return 0;
}
