#include "IdleState.h"
#include "GameManager.h"


void
 IdleState::OnEnter(Boid& boid)
{
  boid.m_data.m_followPathMagnitude = 0.0f; 
}

StateType
IdleState::OnUpdate(float deltaTime, class Boid &boid)
{
  GameManager& gm = GameManager::getInstance();
  auto firstIter = gm.getBeginningIter();
  auto endingIter = gm.getEndingIter();

  for(; firstIter != endingIter; ++firstIter )
  {
    if ((boid.m_data.m_position - firstIter->m_data.m_position).length() < 100.0f )
    {
      return StateType::FollowCourse;
    }
  }

  
 return StateType::Idle;
}

void
IdleState::OnExit(Boid &boid)
{
  boid.m_data.m_followPathMagnitude = 2.0f;
}

