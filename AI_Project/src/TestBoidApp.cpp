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

  m_mousePosition = Vec2(0.0f,0.0f);

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

void 
TestBoidApp::handleInput()
{
  
  sf::Event event;
  while( m_window->pollEvent(event) )
  {
    if( event.type == sf::Event::Closed )
      m_window->close();

    if(event.type == sf::Event::MouseMoved )
    {
      m_mousePosition = Vec2(event.mouseMove.x, event.mouseMove.y);
    }
  }

}

void 
TestBoidApp::handleBoids()
{
  m_boid->addForce(m_boid->seek(m_boid->m_position,
                   m_mousePosition));

  m_boid->update(m_deltaTime);
}

int
TestBoidApp::mainLoop()
{
  while( m_window->isOpen() )
  {
    m_timer.StartTiming();

    handleInput();

    handleBoids();


    m_window->clear();
    m_window->draw(m_boid->m_shape);
    m_window->display();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }


  return 0;
}
