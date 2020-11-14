#include "FSMScoreBord.h"
#include "GameManager.h"

FSMScoreBord::FSMScoreBord()
:m_states(4,nullptr)
{
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

  m_positions.resize(gm.getBoidContainerRef().size());
  for(auto& elem : UI )
  {
    elem.m_ptrBoid = &gm.getBoidContainerRef().at(i);
    m_positions.at(i) = elem.getPosition();
    
    ++i;
  }

  m_lapCount.m_currentCheckPoints = gm.getPathContainerRef().size();

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
