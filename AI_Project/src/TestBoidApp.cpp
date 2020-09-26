#include "TestBoidApp.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "GameManager.h"

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
  std::random_device rd{};
  std::srand(rd());

  m_deltaTime = 0.0f;

  m_screenHeight = 720;
  m_screenWidth = 1200;

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

      const BoidDescriptor fleeDesc = Boid::createFleeBoidDescriptor
      (
        m_mousePosition->m_data.m_position,
        Vec2(static_cast< float >(m_screenWidth) * .5f, static_cast< float >(m_screenHeight) * .4f)
      );

      const BoidDescriptor arriveBoidDesc = Boid::createArrivingBoidDescriptor
      (
        m_mousePosition->m_data.m_position,
        Vec2(static_cast< float >(m_screenWidth) * 0.55f, static_cast< float >(m_screenHeight) * .6f)
      );

      m_groupBoids.emplace_back(Boid(seekDesc));
      m_groupBoids.emplace_back(Boid(fleeDesc));
      m_groupBoids.emplace_back(Boid(arriveBoidDesc));

      const BoidDescriptor pursueDesc = Boid::createPursueBoidDescriptor
      (
        m_groupBoids.at(0),
        Vec2(static_cast< float >(m_screenWidth), static_cast< float >(m_screenHeight) * .6f),
        1.5f,
        0.45f
      );

      m_groupBoids.emplace_back(Boid(pursueDesc));

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
      for( auto& boid : m_groupBoids )
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
  for(auto &boid : m_groupBoids )
  {
    boid.update(m_deltaTime); 
  }
}

void 
TestBoidApp::handleRendering()
{
  m_window->clear();
  for(auto &boid : m_groupBoids )
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


  return 0;
}
