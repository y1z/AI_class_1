#include "ExamApp.h"
#include "GameManager.h"
#include "FSMScoreBord.h"


#include <iostream>
#include <string>
#include <random>

namespace fs = std::filesystem;
using namespace std::literals::string_literals;

ExamApp::ExamApp()
  :BaseApp()
{
  m_path = fs::current_path();
}

int
ExamApp::run()
{
  if( -1 == init(1920, 1080) )
  {
    return -1;
  }

  return mainLoop();
}

int
ExamApp::init(unsigned int width,
              unsigned int height)
{
  GameManager::StartUp(nullptr);
  GameManager& gameMan = GameManager::getInstance();
  m_screenWidth = width;
  m_screenHeight = height;

  std::random_device rd{};
  std::srand(rd());

  const std::string characterNames[] =
  {
    std::string(R"(resources\char_blue.png)") ,
    std::string(R"(resources\char_bluffy.png)") ,
    std::string(R"(resources\char_cha-ching.png)") ,
    std::string(R"(resources\char_just-m.png)") ,

    std::string(R"(resources\char_liario.png)") ,
    std::string(R"(resources\char_lumi.png)") ,
    std::string(R"(resources\char_red.png)") ,
    std::string(R"(resources\char_xzjiors.png)") ,
  };

  const size_t stringSize = sizeof(std::string);
  const size_t nameTotal = sizeof(characterNames) / stringSize;

  for( size_t i = 0u; i < nameTotal; ++i )
  {
    const UIRectangleDesc characterDescriptor
    (
      100,
      100,
      sf::Vector2f(m_screenWidth - 100, 110 * (i + 1)),
      characterNames[i]
    );
    m_manager.addRectangle(characterDescriptor);
  }

  try
  {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                                  "Boid test",
                                                  sf::Style::Default);

    m_mousePos = std::make_unique<Boid>();

    const unsigned int one10thOfWidth = m_screenWidth / 10;
    const unsigned int one10thOfHeight = m_screenHeight / 10;
    for( int i = 1; i < 10; ++i )
    {
      const FollowPathNode node(Vec2(one10thOfWidth * i, one10thOfHeight * i),
                                50.0f);

      gameMan.addNodeToGlobalPath(node);
    }


    const FollowPathNode endPoint(Vec2((m_screenWidth / 10) * 5,
                                  0),
                                  80.0f);
    gameMan.addNodeToGlobalPath(endPoint);

    for( int i = 0; i < 10; ++i )
    {
      BoidDescriptor followBoid = Boid::createFollowPathBoidDescriptor
      (gameMan.getPathContainerRef(),
       Vec2((i * 35), 500),
       0.75f + (i * 0.09f)
      );
      followBoid.m_fleeTargetPosition = &m_mousePos->m_data.m_position;
      followBoid.m_fleeMagnitude = 7.0f;
      followBoid.m_fleeRadius = m_mousePos->m_data.m_shape.getRadius() + 50.0f;

      gameMan.addBoidToGame(followBoid);
    }

  }
  catch( std::exception& e )
  {
    std::cerr << e.what() << "\n\n";
  }


  return 0;
}

void
ExamApp::handleInput()
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
      m_mousePos->m_data.m_position = Vec2(event.mouseMove.x, event.mouseMove.y);
    }
    //if( sf::Keyboard::D == event.key.code )
    //{

    //  for( auto& boid : gm.getBoidContainerRef() )
    //  {
    //    boid.destroy();
    //  }

    //}
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
ExamApp::handleBoid()
{
  GameManager& gm = GameManager::getInstance();

  for( auto& boid : gm.getBoidContainerRef() )
  {
    boid.update(m_deltaTime);
  }
}

void
ExamApp::handleDraw()
{

  GameManager& gameMan = GameManager::getInstance();
  m_window->clear();
  gameMan.drawPath(*m_window);

  for( auto& boid : gameMan.getBoidContainerRef() )
  {
    boid.draw(*m_window);
  }


  m_manager.draw(*m_window);
  m_window->display();
}

int
ExamApp::mainLoop()
{
  GameManager& gameMan = GameManager::getInstance();
  gameMan.setupGroup();
  FSMScoreBord stateMachine;
  stateMachine.init(m_manager);
  while( m_window->isOpen() )
  {
    m_timer.StartTiming();
    handleBoid();
    stateMachine.run(m_manager);

    handleInput();

    handleDraw();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }


  return 0;
}
