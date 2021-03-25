#include "FSM.h"
#include "IdleState.h"
#include "FollowCourse.h"
#include "GameManager.h"
#include "Racer.h"


FSM::FSM()
{
  m_states.fill(nullptr);

  m_states.at(static_cast< enumIndex >(StateType::Idle)) = new IdleState();
  m_states.at(static_cast< enumIndex >(StateType::FollowCourse)) = new FollowCourseState();
}

FSM::~FSM()
{

  for( BaseState* statePtr : m_states )
  {
    if( nullptr != statePtr )
    {
      delete statePtr;
    }
  }

}

int
FSM::run(const float deltaTime)
{
  GameManager& gm = GameManager::getInstance();

  for( auto& agent : gm.getAgentContainerRef() )
  {
    auto& boidRef = agent.getBoid();
    const StateType currentStateType = boidRef.getStateType();
    BaseState* currentState = m_states.at(static_cast< enumIndex >(currentStateType));
    if( nullptr != currentState )
    {
      const StateType stateTypeAfterUpdate = currentState->OnUpdate(deltaTime, boidRef);

      if( stateTypeAfterUpdate != currentStateType )
      {
        currentState->OnExit(boidRef);
        currentState = m_states.at(static_cast< enumIndex >(currentStateType));
        currentState->OnEnter(boidRef);
      }
    }
    else
    {
      return -1;
    }
  }

  return 0;
}

