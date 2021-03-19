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
s_pathToLevelOne = "resources/saves/level_1.txt";

constexpr static const char*
s_pathToSaveSpriteAtlus= "resources/sprite_sheet/mirrored_image_sprite.png";

constexpr static const char*
s_pathToFront = "resources/fonts/Gamepixies-8MO6n.ttf";


fs::path
openFilePath(BaseApp* app);

int
closeApp(BaseApp* app);

int
loadLevelOne(BaseApp* app);


EditorApp::EditorApp()
  : BaseApp() {}

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

void
EditorApp::closeWindow() {
  m_window->close();
}

int
EditorApp::mainLoop() {
  auto& gameMan = GameManager::getInstance();
  gameMan.setupGroup();
  auto& container = gameMan.getAgentContainerRef();

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
EditorApp::menuLoop() {

  while (m_stateMachine->isStateMachineActive() && m_window->isOpen()) {
    m_window->clear();

    m_timer.StartTiming();
    handleInput();

    m_stateMachine->update(m_mouseData, m_deltaTime);
    m_stateMachine->render(m_window.get());

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();

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
      m_testText = make_unique<UIText>();
      UITextDescriptor desc;
      desc.pathToFont = s_pathToFront;
      desc.textString = "dslkfjdsjfdsk;ljfklsdjfklsjfk;ldsjflkjdsk;lfjdkf";
      desc.textFillColor = sf::Color::Blue;
      m_testText->init(desc);
    }

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

  std::vector<UISceneDesc> descriptors;

  auto const halfScreenWidth = static_cast<float>(m_screenWidth) * .5f;
  auto const halfScreenHeight = static_cast<float>(m_screenHeight) * .5f;

  {
    UISceneDesc menuScene;
    const UIRectangle playRect(UIRectangleDesc(300, 200,
                               sf::Vector2f(halfScreenWidth, 300),
                               "", sf::Color::Green));

    const UIRectangle exitRect(UIRectangleDesc(300, 200,
                               sf::Vector2f(halfScreenWidth, 600),
                               "", sf::Color::Red));


    {
      UITextDescriptor disc;
      disc.pathToFont = s_pathToFront;
      disc.textString = " play button";
      disc.textFillColor = sf::Color::Black;
      disc.textOuterColor = sf::Color::Blue;
      disc.textSize = 50;

      menuScene.AddElement(playRect, 1, []() {}, disc);

      disc.textString = " exit button";
      menuScene.AddElement(exitRect, UIScene::NOMORE_SCENES_ID, closeApp, disc);
    }

    menuScene.ID = 0;

    descriptors.push_back(menuScene);
  }

  {
    UISceneDesc levelSelect;
    const UIRectangle levelOneRect(UIRectangleDesc(300, 200,
                                   sf::Vector2f(halfScreenWidth, 300),
                                   "", sf::Color::Yellow));

    UITextDescriptor disc;
    disc.pathToFont = s_pathToFront;
    disc.textString = " play button";
    disc.textFillColor = sf::Color::Black;
    disc.textOuterColor = sf::Color::Blue;
    disc.textSize = 50;
    levelSelect.AddElement(levelOneRect, UIScene::NOMORE_SCENES_ID, loadLevelOne, disc);
    levelSelect.ID = 1;

    descriptors.emplace_back(levelSelect);
  }


  m_stateMachine->init(descriptors, this);
  return true;
}

RESULT_APP_STAGES::E
EditorApp::handleDraw() {
  m_window->clear();

  auto& gm = GameManager::getInstance();
  //m_spriteAtlas->draw(*m_window);
  m_gameMap->draw(*m_window);
  gm.drawRacers(*m_window);
  m_testText->draw(m_window.get());
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
      m_mouseData.m_mousePosition = Vec2(static_cast<float>(event.mouseMove.x),
                                         static_cast<float>(event.mouseMove.y));
    }

    if (sf::Event::MouseButtonReleased == event.type) {
      // m_mouseData.m_mouseAccion = event.mouseButton.button;
      m_mouseData.setMouseAccion(event.mouseButton.button) ;
    }

    if (sf::Event::MouseButtonPressed == event.type) {
      m_mouseData.setMouseAccion(event.mouseButton.button) ;
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
    followBoid.m_fleeTargetPosition = &m_mouseData.m_mousePosition;
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

int
closeApp(BaseApp* app) {
  app->closeWindow();
  return 0;
}

int
loadLevelOne(BaseApp* app) {
  assert(nullptr != app);
  auto gameApp = reinterpret_cast<EditorApp*>(app);
  gameApp->createPath(s_pathToLevelOne);

  return 0;
}

