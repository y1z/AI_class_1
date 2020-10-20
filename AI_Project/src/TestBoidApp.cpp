#include "TestBoidApp.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "GameManager.h"
#include "GlobalValues.h"

#include <iostream>
#include <random>

int
TestBoidApp::run()
{
  if( -1 == init() )
    return -1;


  return mainLoop();
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

  for(int i = 1; i < 10 ; ++i)
  {
    const FollowPathNode node(Vec2(m_screenWidth / (1 + i), m_screenHeight / (1 + i)),
                              std::cos(gvar::eighthPi * static_cast<float> (i)) * 500 + (m_screenHeight / 2u));

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

    {

      const BoidDescriptor seekDesc = Boid::createSeekingBoidDescriptor
      (
        m_mousePosition->m_data.m_position,
        Vec2(static_cast< float >(m_screenWidth) * .6f, static_cast< float >(m_screenHeight) * .3f)
      );

      gameMan.addBoidToGame(seekDesc);

      for(int i = 0; i < 10; ++i )
      {
        const BoidDescriptor followBoid = Boid::createFollowPathBoidDescriptor
        (gameMan.m_globalPath,
         Vec2((i * 30),1000),
         0.35
        );

        gameMan.addBoidToGame(followBoid);
      }

    }

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

      for(auto& boid : gm )
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

  for( auto& boid : gm )
  {
    boid.update(m_deltaTime);
  }

}

void 
TestBoidApp::handleRendering()
{
  GameManager& gm = GameManager::getInstance();
  m_window->clear();
  for(auto &boid : gm )
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


