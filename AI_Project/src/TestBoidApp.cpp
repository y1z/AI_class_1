#include "TestBoidApp.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <ctime>
#include <iostream>

int
TestBoidApp::run()
{
  if( -1 == init() )
    return -1;


  return loop();
}

int
TestBoidApp::init()
{
  std::srand(time(nullptr));
  try
  {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(600, 600), "Boid test");
    m_boid = std::make_unique<Boid>(Vec2(10.f, 0.f));
  }
  catch( const std::exception& e )
  {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return 0;
}

int
TestBoidApp::loop()
{
  sf::Event event;
  m_deltaTime = 0.0f;

  while( m_window->isOpen() )
  {
    m_timer.StartTiming();
    while( m_window->pollEvent(event) )
    {
      if( event.type == sf::Event::Closed )
        m_window->close();
    }

    m_boid->addForce(m_boid->seek(m_boid->m_position, Vec2(50.0f, 1.0f)));

    m_boid->update(m_deltaTime);

    m_window->clear();
    m_window->draw(m_boid->m_shape);
    m_window->display();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }


  return 0;
}
