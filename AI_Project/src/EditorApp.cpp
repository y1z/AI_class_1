#include <iostream>
#include "util.h"
#include "EditorApp.h"

namespace fs = std::filesystem;

using std::make_unique;

constexpr static const char*
s_pathToTextDefault = "resources/test_doc.txt";

constexpr static const char*
s_pathToAtlasDefault = "resources/sprite_sheet/sprite_sheet_mario.png";


EditorApp::EditorApp()
  : BaseApp(), m_mousePos(Vec2(0.0f, 0.0f))
{}

int
EditorApp::run(unsigned int screenWidth,
               unsigned int screenHeight) {
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  if (-1 == init())
  {
    return -1;
  }

  return mainLoop();
}

int
EditorApp::mainLoop() {
  auto& gameMan = GameManager::getInstance();
  gameMan.setupGroup();

  for (auto& elem : gameMan.getAgentContainerRef()) {
    elem.m_atlasPtr = m_spriteAtlas.get();
  }

  while (m_window->isOpen()) {

    m_timer.StartTiming();
    handleRacers();

    handleInput();

    handleDraw();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
  }

  return 0;
}

int
EditorApp::init() {

  try {

    GameManager::StartUp(nullptr);

    m_window = make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                             sf::String(" app"),
                                             sf::Style::Default);

    m_spriteAtlas = make_unique<SpriteAtlas>();

    m_gameMap = make_unique<GameMap>();

    {
      const fs::path pathToText = fs::path(m_initialPath).append(s_pathToTextDefault);
      m_file = util::loadFileToString(pathToText.generic_string());
      if ("Error" == m_file) {
        return -1;
      }
    }

    {
      const fs::path pathToAtlas = fs::path(m_initialPath).append(s_pathToAtlasDefault);
      if (!createAtlas(pathToAtlas)) {
        return -1;
      }
    }

    createPath();

    createRacer();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}

RESULT_APP_STAGES::E
EditorApp::handleDraw() {
  m_window->clear();
  auto& gm = GameManager::getInstance();
  gm.drawRacers(*m_window);
  m_spriteAtlas->draw(*m_window);
  gm.drawPath(*m_window);
  m_window->display();
  return RESULT_APP_STAGES::NO_ERROR;
}

RESULT_APP_STAGES::E
EditorApp::handleInput() {

  sf::Event event;
  while (m_window->pollEvent(event)) {
    if (sf::Event::Closed == event.type ||
        sf::Keyboard::Escape == event.key.code) {
      m_window->close();
    }


    if (sf::Event::MouseMoved == event.type) {
      m_mousePos = Vec2(event.mouseMove.x, event.mouseMove.y);
    }

    if(sf::Event::KeyPressed == event.type)
    {
      if(sf::Keyboard::S == event.key.code)
      {

      }

    }

  }

  return RESULT_APP_STAGES::E::NO_ERROR;
}

RESULT_APP_STAGES::E
EditorApp::handleRacers() {
  auto& gm = GameManager::getInstance();

  for (auto& racer : gm.getAgentContainerRef() ) {
    racer.update(m_deltaTime);
  }

  return RESULT_APP_STAGES::E::kERROR;
}

bool
EditorApp::createAtlas(const std::filesystem::path& pathToAtlas) const {

  const std::vector<sf::IntRect> rectSequence =
    util::createHorizontalIntRectSequence(sf::Vector2i(0, 0), sf::Vector2i(25, 25), 2);

  const SpriteAtlasDesc desc(pathToAtlas, rectSequence);

  const bool isAtlasInitialized = m_spriteAtlas->init(desc);

  const sf::Color backGroundColor = m_spriteAtlas->getColorOfPixel(0u, 0u);
  m_spriteAtlas->makeColorTransparent(backGroundColor);

  return isAtlasInitialized;
}

void
EditorApp::createPath(const std::filesystem::path& pathToFile) {
  GameManager& gameMan = GameManager::getInstance();
  if ("" != pathToFile) {

  }
  else {
    const unsigned int one10thOfWidth = m_screenWidth / 10;
    const unsigned int one10thOfHeight = m_screenHeight / 10;

    std::vector<FollowPathNode> path;
    for (unsigned int i = 1u; i < 10u; ++i) {
      const FollowPathNode node(Vec2(one10thOfWidth * i, one10thOfHeight * i),
                                40.0f);

      path.emplace_back(node);
      //gameMan.addNodeToGlobalPath(node);
    }
    const FollowPathNode endPoint(Vec2((m_screenWidth / 10) * 5,
                                  0),
                                  80.0f);
    path.emplace_back(endPoint);
    m_gameMap->createMap(path);
  }
}

bool
EditorApp::createRacer() {
  GameManager& gameMan = GameManager::getInstance();
  for (int i = 0; i < 10; ++i) {
    BoidDescriptor followBoid = Boid::createFollowPathBoidDescriptor
    (   gameMan.getPathContainerRef(),
     Vec2((i * 35), 500),
     0.75f + util::randomRangeFloat(0.01f, 1.01f)
    );
    followBoid.m_fleeTargetPosition = &m_mousePos;
    followBoid.m_fleeMagnitude = 7.0f;
    followBoid.m_fleeRadius = 100.0f;

    gameMan.addRacerToGame(followBoid);
  }

  return true;
}


