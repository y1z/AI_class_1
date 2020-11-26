#include "StateMachineTestApp.h"
#include "GameManager.h"
#include "GlobalValues.h"

int
StateMachineTestApp::run()
{
  if( -1 == init() )
    return -1;

  return mainLoop();
}

int
StateMachineTestApp::init()
{
  const unsigned int halfScreenWidth = m_screenWidth / 2;
  const unsigned int halfScreenHeight = m_screenHeight / 2;

  m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                                "State machine test",
                                                sf::Style::Default);

  m_stateMachine = std::make_unique<FSM>();

  GameManagerDescriptor descriptor;
  for( int i = 0; i < 8; ++i )
  {
    Vec2 Position = Vec2(std::cosf(i * gvar::eighthPi) * 200.0f, std::sinf(i * gvar::eighthPi) * 200.0f);
    Position += Vec2(halfScreenWidth, halfScreenHeight);
    descriptor.m_pathData.emplace_back(FollowPathNode(Position));
  }

  for( int i = 0; i < 8; ++i )
  {
    auto boidDesc = BoidDescriptor();
    boidDesc.m_followPathMagnitude = 2.0f;
    boidDesc.m_cycleFollowPath = true;
    boidDesc.m_pathNodes = descriptor.m_pathData;
    descriptor.m_boidDescriptors.emplace_back(boidDesc);
  }



  GameManager::StartUp(&descriptor);

  return 0;
}

int
StateMachineTestApp::mainLoop()
{
  while( m_window->isOpen() )
  {
    m_timer.StartTiming();

    m_stateMachine->run(m_deltaTime);

    handleInput();

    handleRender();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }

  GameManager::ShutDown();
  return 0;
}

void
StateMachineTestApp::handleInput()
{
  sf::Event event;
  while( m_window->pollEvent(event) )
  {
    if( sf::Event::Closed == event.type ||
       sf::Keyboard::Escape == event.key.code )
    {
      m_window->close();
    }
  }
}

void 
StateMachineTestApp::handleRender()
{
  GameManager& gm = GameManager::getInstance();
  m_window->clear();

  for( auto& agent : gm.getAgentContainerRef() )
  {
    agent.draw(*m_window);
  }

  m_window->display();
}
