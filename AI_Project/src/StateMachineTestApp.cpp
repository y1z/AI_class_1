#include "StateMachineTestApp.h"
#include "GameManager.h"
#include "GlobalValues.h"

int
StateMachineTestApp::run()
{

  if( -1 == start() )
    return -1;




  return mainLoop();
}

int
StateMachineTestApp::start()
{
  const unsigned int halfScreenWidth = m_screenWidth / 2;
  const unsigned int halfScreenHeight = m_screenHeight / 2;

  m_deltaTime = 0.0f;

  m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                                "State machine test",
                                                sf::Style::Default);


  GameManagerDescriptor descriptor;
  for( int i = 0; i < 8; ++i )
  {
    Vec2 Position = Vec2(std::cosf(i * gvar::halfQuarterPi), std::sinf(i * gvar::halfQuarterPi));
    Position += Vec2(halfScreenWidth, halfScreenHeight);
    descriptor.m_path.emplace_back(FollowPathNode(Position));
  }

  for( int i = 0; i < 8; ++i )
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
  while( m_window->isOpen() )
  {
    GameManager& gm = GameManager::getInstance();
    m_timer.StartTiming();

    auto beginnigIter = gm.begin();
    auto endIter = gm.end();

    handleInput();

    m_window->clear();

    for(;beginnigIter != endIter; ++beginnigIter )
    {
      m_window->draw(beginnigIter->m_data.m_shape);
    }

    m_window->display();



    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }

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
