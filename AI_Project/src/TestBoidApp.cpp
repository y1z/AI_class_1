#include "TestBoidApp.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "GameManager.h"
#include "GlobalValues.h"
#include "Racer.h"

#include <iostream>
#include <random>

int
TestBoidApp::run(unsigned int screenWith,
                 unsigned int screenHeight)
{
  if( -1 == init() )
    return -1;


  return mainLoop();
}

void
TestBoidApp::closeWindow() {
  m_window->close();
}

int
TestBoidApp::init()
{
  GameManager::StartUp(nullptr);
  GameManager& gameMan = GameManager::getInstance();

  std::random_device rd{};
  std::srand(rd());

  m_deltaTime = 0.0f;

  m_screenHeight = 1080;
  m_screenWidth = 1920;

  const unsigned int one10thOfWidth = m_screenWidth / 10;
  const unsigned int one10thOfHeight = m_screenHeight / 10;
  for( int i = 1; i < 10; ++i )
  {
    const FollowPathNode node(Vec2( one10thOfWidth * i , one10thOfHeight * i),
                              50.0f);

    gameMan.addNodeToGlobalPath(node);
  }



  try
  {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                                  "Boid test",
                                                  sf::Style::Default);


    m_window->setVerticalSyncEnabled(true);
    m_window->setFramerateLimit(1060u);

    m_mousePosition = std::make_unique<Boid>();
    m_mousePosition->init(BoidDescriptor());


    for( int i = 0; i < 10; ++i )
    {
      const BoidDescriptor followBoid = Boid::createFollowPathBoidDescriptor
      (gameMan.getPathContainerRef(),
       Vec2((i * 35), 500),
       0.75f
      );

      gameMan.addRacerToGame(followBoid);
    }

    gameMan.setupGroup();
  }
  catch( const std::exception& e )
  {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return 0;
}

void
TestBoidApp::handleInput()
{
  GameManager& gm = GameManager::getInstance();
  sf::Event event;
  while( m_window->pollEvent(event) )
  {
    if( sf::Event::Closed == event.type ||
       sf::Keyboard::Escape == event.key.code )
    {
      m_window->close();
    }
    if( sf::Keyboard::D == event.key.code )
    {

      for( auto& boid : gm.getAgentContainerRef() )
      {
        boid.destroy();
      }

    }

    if( sf::Event::MouseMoved == event.type )
    {
      m_mousePosition->m_data.m_position = Vec2(event.mouseMove.x, event.mouseMove.y);
    }

    if( sf::Event::Resized == event.type )
    {
      sf::View const newView
      (
        sf::FloatRect(0, 0, event.size.width, event.size.height)
      );
      m_window->setView(newView);
    }

  }

}

void
TestBoidApp::handleBoids()
{
  GameManager& gm = GameManager::getInstance();

  for( auto& boid : gm.getAgentContainerRef() )
  {
    boid.update(m_deltaTime);
  }

}

void
TestBoidApp::handleRendering()
{
  GameManager& gm = GameManager::getInstance();
  m_window->clear();
  gm.drawPath(*m_window);

#if !NDEBUG
  gm.drawAndClearDebug(*m_window);
#endif // !NDEBUG

  for( auto& boid : gm.getAgentContainerRef() )
  {
    boid.draw(*m_window);
  }
  m_window->display();
}

int
TestBoidApp::mainLoop()
{
  while( m_window->isOpen() )
  {
    m_timer.StartTiming();

    handleInput();

    handleBoids();

    handleRendering();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }


  GameManager::ShutDown();
  return 0;
}


