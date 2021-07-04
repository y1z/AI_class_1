#include "FSM.h"
#include "IdleState.h"
#include "FollowCourse.h"
#include "GameManager.h"

FSM::FSM()
{
  m_states.fill(nullptr);

  m_states.at(static_cast< int >(StateType::Idle)) = new IdleState();
  m_states.at(static_cast< int >(StateType::FollowCourse)) = new FollowCourseState();
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

  for(auto &boid : gm )
  {
    const StateType currentStateType = boid.getStateType();
    BaseState* currentState = m_states.at(static_cast< int >(currentStateType));
    if( nullptr != currentState )
    {
      const StateType stateTypeAfterUpdate = currentState->OnUpdate(deltaTime, boid);

      if(stateTypeAfterUpdate != currentStateType )
      {
        currentState->OnExit(boid);
        currentState = m_states.at(static_cast< int >(currentStateType));
        currentState->OnEnter(boid);
      }
    }
    else
    {
      return -1;
    }
  }

  return 0;
}

