#include "FollowCourse.h"
#include "GameManager.h"

void 
FollowCourseState::OnEnter(Boid& boid)
{
  if(boid.m_data.m_pathNodes.empty())
  {
    boid.m_data.m_pathNodes = GameManager::getInstance().m_globalPath;
  }
  boid.m_data.m_followPathMagnitude = 2.5f;
  boid.m_data.m_cycleFollowPath = true;
}

StateType 
FollowCourseState::OnUpdate(float deltaTime, Boid& boid)
{
  GameManager& gm = GameManager::getInstance();
  boid.update(deltaTime);

  auto beginningIter = gm.begin();
  auto endingIter = gm.end();
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
FollowCourseState::OnExit(Boid& boid)
{
  boid.m_data.m_aggressiveTime = 0.0f;
}
