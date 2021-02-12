#include "ExamApp.h"
#include "GameManager.h"
#include "FSMScoreBord.h"
#include "util.h"


#include <iostream>
#include <string>
#include <random>

namespace fs = std::filesystem;
using namespace std::literals::string_literals;

ExamApp::ExamApp()
  :BaseApp() {
  m_path = fs::current_path();
}

int
ExamApp::run(unsigned int screenWith,
             unsigned int screenHeight) {
  if (-1 == init(screenWith, screenHeight)) {
    return -1;
  }

  return mainLoop();
}

int
ExamApp::init(unsigned int width,
              unsigned int height) {
  GameManager::StartUp(nullptr);
  m_screenWidth = width;
  m_screenHeight = height;

  std::random_device rd{};
  std::srand(rd());


  try {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                                  sf::String("final app"),
                                                  sf::Style::Default);

    m_atlasPtr = std::make_unique<SpriteAtlas>();

    m_mousePos = std::make_unique<Boid>();

    createPath();

    const bool areRacersCorrect = createRacers();

    const bool arePortraitsCorrect = createRacersPortraits();

    const fs::path pathToSpriteSheet = m_path.append(R"..(resources/sprite_sheet/sprite_sheet_mario.png)..");
    if (!createAtlas(pathToSpriteSheet)) {
      return -1;
    }
    if (!(areRacersCorrect && arePortraitsCorrect)) {
      return -1;
    }

  }
  catch (std::exception& e) {
    std::cerr << e.what() << "\n\n";
    return -1;
  }

  return 0;
}

bool
ExamApp::createRacers()const {
  GameManager& gameMan = GameManager::getInstance();
  for (int i = 0; i < 10; ++i) {
    BoidDescriptor followBoid = Boid::createFollowPathBoidDescriptor
    (gameMan.getPathContainerRef(),
     Vec2((i * 35), 500),
     0.75f + util::randomRangeFloat(0.01f, 1.01f)
    );
    followBoid.m_fleeTargetPosition = &m_mousePos->m_data.m_position;
    followBoid.m_fleeMagnitude = 7.0f;
    followBoid.m_fleeRadius = m_mousePos->m_data.m_shape.getRadius() + 50.0f;

    gameMan.addRacerToGame(followBoid);
  }

  return true;
}

void
ExamApp::createPath()const {

  GameManager& gameMan = GameManager::getInstance();

  const unsigned int one10thOfWidth = m_screenWidth / 10;
  const unsigned int one10thOfHeight = m_screenHeight / 10;

  for (unsigned int i = 1u; i < 10u; ++i) {
    const FollowPathNode node(Vec2(one10thOfWidth * i, one10thOfHeight * i),
                              40.0f);

    gameMan.addNodeToGlobalPath(node);
  }
  const FollowPathNode endPoint(Vec2((m_screenWidth / 10) * 5,
                                0),
                                80.0f);

  gameMan.addNodeToGlobalPath(endPoint);
}

bool
ExamApp::createAtlas(const std::filesystem::path& pathToAtlas) const {
  const SpriteAtlasDesc desc(pathToAtlas,
                             { sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(25, 25)) });
  const bool isAtlasInitialized = m_atlasPtr->init(desc);

  const sf::Color backGroundColor = m_atlasPtr->getColorOfPixel(0u, 0u);
  m_atlasPtr->makeColorTransparent(backGroundColor);

  return isAtlasInitialized;
}

bool
ExamApp::createRacersPortraits() {
  static const std::array<std::string, 8> characterNames =
  {
    std::string(R"(resources/char_blue.png)"),
    std::string(R"(resources/char_bluffy.png)"),
    std::string(R"(resources/char_cha-ching.png)"),
    std::string(R"(resources/char_just-m.png)"),

    std::string(R"(resources/char_liario.png)"),
    std::string(R"(resources/char_lumi.png)"),
    std::string(R"(resources/char_red.png)"),
    std::string(R"(resources/char_xzjiors.png)"),
  };

  for (const auto& name : characterNames) {
    const bool isValidPath = fs::exists(name) && !fs::is_directory(name);
    if (!isValidPath) {
      std::cerr << "The path {" << name << "}\n";
      return false;
    }
  }

  const size_t nameTotal = sizeof(characterNames) / sizeof(std::string);

  for (size_t i = 0u; i < nameTotal; ++i) {
    const UIRectangleDesc characterDescriptor
    (
      100,
      100,
      sf::Vector2f(m_screenWidth - 100, 110 * (i + 1)),
      characterNames[i]
    );
    m_manager.addRectangle(characterDescriptor);
  }
  return true;
}

void
ExamApp::handleInput() {
  sf::Event event;
  while (m_window->pollEvent(event)) {
    if (sf::Event::Closed == event.type ||
        sf::Keyboard::Escape == event.key.code) {
      m_window->close();
    }


    if (sf::Event::MouseMoved == event.type) {
      m_mousePos->m_data.m_position = Vec2(event.mouseMove.x, event.mouseMove.y);
    }

    if (sf::Event::Resized == event.type) {
      sf::View const newView
      (
        sf::FloatRect(0, 0, event.size.width, event.size.height)
      );
      m_window->setView(newView);
    }

  }
}

void
ExamApp::handleRacers() {
  GameManager& gm = GameManager::getInstance();

  for (auto& agent : gm.getAgentContainerRef()) {
    agent.update(m_deltaTime);
  }
}

void
ExamApp::handleDraw() {
  GameManager& gameMan = GameManager::getInstance();
  m_window->clear();
  gameMan.drawPath(*m_window);

  for (auto& Agent : gameMan.getAgentContainerRef()) {
    Agent.draw(*m_window);
  }

  m_manager.draw(*m_window);
  m_atlasPtr->draw(*m_window);
  m_window->display();
}

int
ExamApp::mainLoop() {
  GameManager& gameMan = GameManager::getInstance();
  gameMan.setupGroup();
  FSMScoreBord stateMachine;
  stateMachine.init(m_manager);

  for (auto& elem : gameMan.getAgentContainerRef()) {
    elem.m_atlasPtr = m_atlasPtr.get();
  }

  while (m_window->isOpen()) {
    m_timer.StartTiming();
    handleRacers();
    stateMachine.run(m_manager);

    handleInput();

    handleDraw();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }


  return 0;
}


