#include "TestBoidApp.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

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
  std::random_device rd{};
  std::srand(rd());

  m_deltaTime = 0.0f;

  BoidDescriptor desc = Boid::createDefaultDescriptor();

  m_screenHeight = 720;
  m_screenWidth = 1200;

  desc.m_position = Vec2(m_screenWidth * .5f, m_screenHeight * .5f);

  m_mousePosition.init(Boid::createDefaultDescriptor());


  try
  {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                                  "Boid test",
                                                  sf::Style::Default);

    m_boid = std::make_unique<Boid>(desc);

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

    if( sf::Event::MouseMoved == event.type )
    {
      m_mousePosition.m_data.m_position = Vec2(event.mouseMove.x, event.mouseMove.y);
    }

    if( sf::Event::Resized == event.type )
    {
      sf::View const newView(sf::FloatRect(0, 0, event.size.width, event.size.height));
      m_window->setView(newView);
    }

  }

}

void
TestBoidApp::handleBoids()
{
  m_boid->update(m_deltaTime);
}

void 
TestBoidApp::handleRendering()
{
  m_window->clear();
  m_window->draw(m_boid->m_data.m_shape);
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
