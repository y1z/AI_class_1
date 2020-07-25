#include "FollowCourse.h"
#include "GameManager.h"

void 
FollowCourse::OnEnter(Boid& boid)
{
  if(boid.m_data.m_followPathNodes.empty())
  {
    boid.m_data.m_followPathNodes = GameManager::getInstance().m_globalPath;
  }
  boid.m_data.m_followPathMagnitude = 2.5f;
  boid.m_data.m_cycleFollowPath = true;
}

StateType 
FollowCourse::OnUpdate(float deltaTime, Boid& boid)
{
  GameManager& gm = GameManager::getInstance();
  boid.update(deltaTime);

  auto beginningIter = gm.getBeginningIter();
  auto endingIter = gm.getEndingIter();
  for( ; beginningIter != endingIter; ++beginningIter )
  {
    if( boid.m_data.m_mass < beginningIter->m_data.m_mass &&
       (boid.m_data.m_position - beginningIter->m_data.m_position).length() < 100.0f )
    {
      boid.m_data.m_seekTargetPosition = &beginningIter->m_data.m_position;
      boid.m_data.m_seekMagnitude = 2.5f;

      return StateType::RunOver;
    }
  }

  return StateType::FollowCourse;
}

void 
FollowCourse::OnExit(Boid& boid)
{
  boid.m_data.m_agressiveTime = 0.0f;
}
