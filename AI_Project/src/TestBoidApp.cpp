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

  m_mousePosition = Boid(Vec2(0.0f, 0.0f));
  try
  {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1200, 700),
                                                  "Boid test",
                                                  sf::Style::Default);

    m_boid = std::make_unique<Boid>(Vec2(10.f, 10.f));
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
    if( sf::Event::Closed == event.type )
      m_window->close();

    if( sf::Event::MouseMoved == event.type )
    {
      m_mousePosition.m_position = Vec2(event.mouseMove.x, event.mouseMove.y);
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
  Vec2 force(.0f, .0f);

  //= m_boid->seek(m_boid->m_position, m_mousePosition.m_position, 2);//m_boid->arrive(*m_boid, m_mousePosition, 3, 200.0f);
  force = m_boid->pursue(m_boid->m_position, m_mousePosition, 2.5f, 4);

  m_boid->addForce(force);

  m_boid->update(m_deltaTime);
}

void 
TestBoidApp::handleRendering()
{
  m_window->clear();
  m_window->draw(m_boid->m_shape);
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
