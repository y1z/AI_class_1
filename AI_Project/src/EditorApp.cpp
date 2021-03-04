#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <commdlg.h> // for GetOpenFileName
#undef max
#undef min
#include "util.h"
#include "EditorApp.h"

namespace fs = std::filesystem;

using std::make_unique;

/**
 * NonClass related constants.
 */
constexpr static const char*
s_pathToAtlasDefault = "resources/sprite_sheet/sprite_sheet_mario.png";

constexpr static const char*
s_pathToSaveFileDefault = "resources/saves/test.txt";


fs::path
openFilePath();


EditorApp::EditorApp()
  : BaseApp(), m_mouseData(Vec2(0.0f, 0.0f), 0)
{}

int
EditorApp::run(unsigned int screenWidth,
               unsigned int screenHeight) {
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  if (-1 == init()) {
    return -1;
  }

  return mainLoop();
}

int
EditorApp::mainLoop() {
  auto& gameMan = GameManager::getInstance();
  gameMan.setupGroup();
  auto& container = gameMan.getAgentContainerRef();

  while (true) {
  }

  for (auto& elem : container) {
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

    m_stateMachine = make_unique<UIStateMachine>();

    {
      const fs::path pathToAtlas = fs::path(m_initialPath).append(s_pathToAtlasDefault);
      if (!createAtlas(pathToAtlas)) {
        return -1;
      }
    }
    createMenu();

    createPath();

    createRacer();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}

bool
EditorApp::createMenu() {
  {
    UISceneDesc menuScene;
    const UiRectangle selectRect(UIRectangleDesc(200, 200, sf::Vector2f(300, 300), ""));
    const UiRectangle playRect(UIRectangleDesc(200, 200, sf::Vector2f(300, 600), ""));
    const UiRectangle exitRect(UIRectangleDesc(200, 200, sf::Vector2f(300, 900), ""));

    menuScene.rectangles.push_back(selectRect);
    menuScene.rectangles.push_back(playRect);
    menuScene.rectangles.push_back(exitRect);
    menuScene.ID = 0;
    menuScene.associatedScenes = { 2 , 1, -1 };
    m_stateMachine->init({ menuScene }); //m_scenes.push_back(UIScene(menuScene));
  }

  return true;
}

RESULT_APP_STAGES::E
EditorApp::handleDraw() {
  m_window->clear();

  auto& gm = GameManager::getInstance();
  m_spriteAtlas->draw(*m_window);
  m_gameMap->draw(*m_window);
  gm.drawRacers(*m_window);
  m_window->display();

  return RESULT_APP_STAGES::E::kNO_ERROR;
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

    if (sf::Event::KeyPressed == event.type) {
      if (sf::Keyboard::S == event.key.code) {
        const auto path = fs::path(m_initialPath).append(s_pathToSaveFileDefault);
        m_gameMap->saveMap(path.generic_string());
      }

      if (sf::Keyboard::P == event.key.code) {
        const fs::path p = openFilePath();
        std::cout << p << '\n';
      }

      if (sf::Keyboard::L == event.key.code) {
        const auto path = fs::path(m_initialPath).append(s_pathToSaveFileDefault);
        m_gameMap->loadMap(path);
        auto& gameMan = GameManager::getInstance();

        for (auto& boid : gameMan.getAgentContainerRef()) {
          boid.getBoidData().m_pathNodes = m_gameMap->m_positionData;
        }
      }

    }

  }

  return RESULT_APP_STAGES::E::kNO_ERROR;
}

RESULT_APP_STAGES::E
EditorApp::handleRacers() {
  auto& gm = GameManager::getInstance();
  auto& container = gm.getAgentContainerRef();
  for (auto& racer : container) {
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
  if ("" != pathToFile) {
    m_gameMap->loadMap(pathToFile.generic_string());
  }
  else {
    const unsigned int one10thOfWidth = m_screenWidth / 10;
    const unsigned int one10thOfHeight = m_screenHeight / 10;

    std::vector<FollowPathNode> path;
    for (unsigned int i = 1u; i < 10u; ++i) {
      const FollowPathNode node(Vec2(one10thOfWidth * i, one10thOfHeight * i),
                                40.0f);

      path.emplace_back(node);
    }
    const FollowPathNode endPoint(Vec2((m_screenWidth / 10) * 5, 0),
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
    (m_gameMap->m_positionData,
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

fs::path
openFilePath() {

  /**
   * All text before the first null character is the name we give to the type
   * of files we are looking for what comes after that is the name of the extension
   */
  static constexpr const char* fileTypes = "All files\0*.*\0 \0*.txt\0";

  OPENFILENAMEA File;
  char FileName[MAX_PATH];
  char currentPathDir[MAX_PATH];

  std::memset(&File, 0, sizeof(File));
  std::memset(&FileName, '\0', sizeof(FileName));
  std::memset(&currentPathDir, '\0', sizeof(currentPathDir));

  // save the current directory so we don't change it later
  GetCurrentDirectoryA(sizeof(currentPathDir) - 1, currentPathDir);

  File.lStructSize = sizeof(File);
  File.hwndOwner = nullptr;

  File.lpstrFile = FileName;
  File.lpstrFile[0] = '\0';

  File.nMaxFile = sizeof(FileName);
  File.lpstrFilter = fileTypes;
  // controls which of the file type is chosen by default.
  File.nFilterIndex = 1;

  GetOpenFileNameA(&File);

  SetCurrentDirectoryA(currentPathDir);

  return  fs::path(FileName);

}
