#include "StateMachineTestApp.h"
#include "GameManager.h"
#include "GlobalValues.h"

int 
StateMachineTestApp::run()
{

  if(-1 == start() )
    return -1;




  return mainLoop();
}

int 
StateMachineTestApp::start()
{
  const unsigned int halfScreenWidth = m_screenWidth * 0.5f;
  const  unsigned int halfScreenHeight = m_screenHeight * 0.5f;

  GameManagerDescriptor descriptor;
  for(int i = 0; i < 8; ++i )
  {
    Vec2 Position = Vec2(std::cosf(i * gvar::halfQuarterPi), std::sinf(i * gvar::halfQuarterPi));
    Position += Vec2(halfScreenWidth, halfScreenHeight);
    descriptor.m_path.emplace_back(FollowPathNode(Position));
  }

  for(int i = 0; i < 8; ++i )
  {
    auto boidDesc = Boid::createDefaultDescriptor();
    boidDesc.m_followPathMagnitude = 1.4f;
    boidDesc.m_followPathNodes = descriptor.m_path;
    descriptor.m_boidDescriptors.emplace_back(boidDesc);
  }



 GameManager::StartUp(&descriptor);

  return 0;
}

int 
StateMachineTestApp::mainLoop()
{


  return 0;
}
