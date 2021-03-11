#include "EditorApp.h"
#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <commdlg.h> // for GetOpenFileName
#undef max
#undef min
#include "util.h"
#include "GlobalValues.h"

namespace fs = std::filesystem;

using std::make_unique;

/**
 * NonClass related constants.
 */
constexpr static const char*
s_pathToAtlasDefault = "resources/sprite_sheet/sprite_sheet_mario2.png";

constexpr static const char*
s_pathToSaveFileDefault = "resources/saves/test.txt";

constexpr static const char*
s_pathToSaveSpriteAtlus= "resources/sprite_sheet/mirrored_image_sprite.png";


fs::path
openFilePath(BaseApp* app);


EditorApp::EditorApp()
  : BaseApp(), m_mouseData(Vec2(0.0f, 0.0f), sf::Mouse::Button::ButtonCount) {}

int
EditorApp::run(unsigned int screenWidth,
               unsigned int screenHeight) {
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  if (-1 == init()) {
    return -1;
  }


  if (-1 == menuLoop()) {
    return -1;
  }

  return mainLoop();
}

int
EditorApp::mainLoop() {
  auto& gameMan = GameManager::getInstance();
  gameMan.setupGroup();
  auto& container = gameMan.getAgentContainerRef();


  for (auto& elem : container) {
    elem.m_atlasPtr = m_spriteAtlas.get();
  }

  const float changeRate = 0.8f;
  float totalTime = 0.0f;
  while (m_window->isOpen()) {

    m_timer.StartTiming();
    handleRacers();

    handleInput();

    handleDraw();

    if (totalTime >= changeRate) {
      totalTime = 0.0f;

      for (auto& racer : container) {
        racer.setFrame(12);
      }

    }


    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
    totalTime += m_deltaTime;
  }

  return 0;
}

int
EditorApp::menuLoop() {

  while (m_stateMachine->isStateMachineActive()) {
    m_window->clear();
    handleInput();
    const sf::Vector2f mousePosition = util::vec2ToVector2f(m_mouseData.mousePosition);
    m_stateMachine->update(mousePosition, m_mouseData.mouseAccion);
    m_stateMachine->render(m_window.get());
    m_window->display();
  }

  setUpNewPath();

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
    auto const halfScreenWidth = m_screenWidth / 2.0f;
    const UiRectangle selectRect(UIRectangleDesc(200, 200, sf::Vector2f(halfScreenWidth, 200), "", sf::Color::Yellow));
    const UiRectangle playRect(UIRectangleDesc(200, 200, sf::Vector2f(halfScreenWidth, 400), "", sf::Color::Red));

    menuScene.AddElement(selectRect, -1, std::function<fs::path(BaseApp*)>(openFilePath));
    menuScene.AddElement(playRect, -1);

    menuScene.ID = 0;

    m_stateMachine->init({ menuScene }, this);
  }

  return true;
}

RESULT_APP_STAGES::E
EditorApp::handleDraw() {
  m_window->clear();

  auto& gm = GameManager::getInstance();
  //m_spriteAtlas->draw(*m_window);
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
      m_mouseData.mousePosition = Vec2(event.mouseMove.x, event.mouseMove.y);
    }

    if (sf::Event::MouseButtonPressed == event.type) {
      m_mouseData.mouseAccion = event.mouseButton.button;
    }

    if (sf::Event::KeyPressed == event.type) {

      switch (event.key.code) {
      case sf::Keyboard::S:
      {
        const auto path = fs::path(m_initialPath).append(s_pathToSaveFileDefault);
        m_gameMap->saveMap(path.generic_string());
      }
      break;

      case sf::Keyboard::P:
      {
        auto path = fs::path(m_initialPath).append(s_pathToSaveSpriteAtlus);
        if (m_spriteAtlas->m_atlasTexture->copyToImage().saveToFile(path.generic_string())) {
          std::cout << "saving sprite image to [" << s_pathToSaveSpriteAtlus << "]\n";
        }
      }

      break;
      case sf::Keyboard::L:
      {
        const auto path = fs::path(m_initialPath).append(s_pathToSaveFileDefault);
        m_gameMap->loadMap(path);
        setUpNewPath();
      }
      break;
      default:
      break;
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
    util::createHorizontalIntRectSequence(sf::Vector2i(0, 30), sf::Vector2i(30, 30), 12);

  const std::vector<RotationSegment> rotations =
    util::createRotationSegmentSequence(gvar::halfPi,
                                        gvar::halfPi - gvar::pi,
                                        12);


  const SpriteAtlasDesc desc(pathToAtlas, rectSequence, rotations);

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

void
EditorApp::setUpNewPath() {
  auto& gameMan = GameManager::getInstance();

  for (auto& boid : gameMan.getAgentContainerRef()) {
    boid.getBoidData().m_pathNodes = m_gameMap->m_positionData;
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
    followBoid.m_fleeTargetPosition = &m_mouseData.mousePosition;
    followBoid.m_fleeMagnitude = 7.0f;
    followBoid.m_fleeRadius = 100.0f;

    gameMan.addRacerToGame(followBoid);
  }

  return true;
}

fs::path
openFilePath(BaseApp* app) {

  assert(app != nullptr);
  auto editorApp = dynamic_cast<EditorApp*> (app);
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

  editorApp->createPath(fs::path(FileName));

  SetCurrentDirectoryA(currentPathDir);
  return  fs::path(FileName);

}
