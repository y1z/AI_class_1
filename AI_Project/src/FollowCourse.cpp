#include "FollowCourse.h"
#include "GameManager.h"

void
FollowCourseState::OnEnter(Boid& boid)
{
  if( boid.m_data.m_pathNodes.empty() )
  {
    boid.m_data.m_pathNodes = GameManager::getInstance().getPathContainerRef();
  }
  boid.m_data.m_followPathMagnitude = 2.5f;
  boid.m_data.m_cycleFollowPath = true;
}

StateType
FollowCourseState::OnUpdate(float deltaTime, Boid& boid)
{
  GameManager& gm = GameManager::getInstance();
  boid.update(deltaTime);

  auto beginningIter = gm.getAgentContainerRef().begin();
  const auto endIter = gm.getAgentContainerRef().end();
  for( ; beginningIter != endIter; ++beginningIter )
  {
    auto& boidRef = beginningIter->getBoid();
    if( boid.m_data.m_mass < boidRef.m_data.m_mass &&
       (boid.m_data.m_position - boidRef.m_data.m_position).length() < 100.0f )
    {
      boid.m_data.m_seekTargetPosition = &boidRef.m_data.m_position;
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
