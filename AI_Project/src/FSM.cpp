#include "FSM.h"
#include "IdleState.h"
#include "FollowCourse.h"
#include "GameManager.h"

FSM::FSM()
{
  for(auto* statePtr : m_states )
  {
    statePtr = nullptr;
  }

  m_states.at(( int )StateType::Idle) = new IdleState();
  m_states.at(( int )StateType::FollowCourse) = new FollowCourse();
}

FSM::~FSM()
{
  for(auto* statePtr : m_states )
  {
    if(nullptr!=statePtr )
    {
      delete statePtr;
    }
  }
  
}

int 
FSM::run()
{
  GameManager& gm = GameManager::getInstance();
  auto beginningIter = gm.getBeginningIter();
  auto endingIter = gm.getEndingIter();
  while(beginningIter != endingIter )
  {


    ++beginningIter;
  }


  return 0;
}
