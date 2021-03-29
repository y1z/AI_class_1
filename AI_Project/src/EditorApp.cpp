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
#include "SpriteSheetAndPortriat.h"

namespace fs = std::filesystem;

using std::make_unique;


/**
 * NonClass related constants.
 */
constexpr static SpriteSheetAndPortriat
s_pathsToMarioSprites = SpriteSheetAndPortriat("resources/sprite_sheet/sprite_sheet_mario2.png",
                                               "resources/portraits/mario_portrait.png",
                                               0);

constexpr static SpriteSheetAndPortriat
s_pathsToPeachSprites = SpriteSheetAndPortriat("resources/sprite_sheet/sprite_sheet_peach.png",
                                               "resources/portraits/peach_portrait.png",
                                               1);

constexpr static SpriteSheetAndPortriat
s_pathsToBowserSprites = SpriteSheetAndPortriat("resources/sprite_sheet/sprite_sheet_bowser.png",
                                                "resources/portraits/bowser_portrait.png",
                                                2);

constexpr static SpriteSheetAndPortriat
s_pathsToYoshiSprites = SpriteSheetAndPortriat("resources/sprite_sheet/sprite_sheet_yoshi.png",
                                               "resources/portraits/yoshi_portrait.png",
                                               3);

constexpr static SpriteSheetAndPortriat
s_pathsToKongSprites = SpriteSheetAndPortriat("resources/sprite_sheet/sprite_sheet_kong.png",
                                              "resources/portraits/kong_portrait.png",
                                              4);


constexpr static const char*
s_pathToMusic = "resources/music/WBA Free Track - Skeletal Leaders.ogg";


constexpr static const char*
s_pathToSaveFileDefault = "resources/saves/test.txt";

constexpr static const char*
s_pathToLevel1 = "resources/saves/level_1.txt";

constexpr static const char*
s_pathToLevel2 = "resources/saves/level_2.txt";

constexpr static const char*
s_pathToLevel3 = "resources/saves/level_3.txt";

constexpr static const char*
s_pathToFrontPixels = "resources/fonts/Gamepixies-8MO6n.ttf";

constexpr static const char*
s_pathToFrontDisco = "resources/fonts/DiscoBlingRegular-MjGJ.ttf";

constexpr static const char*
s_pathToCredits = "resources/credits/credits.txt";

constexpr static int32
s_startMenuID = 0;

constexpr static int32
s_levelSelectID = 1;

constexpr static int32
s_creditID = 2;

constexpr static int32
s_characterSelectID = 3;

struct DataOpenFile
{
  DataOpenFile()
    :m_openFileSettings(),
    m_fileName(MAX_PATH, '\0'),
    m_currentDirectory(MAX_PATH, '\0') {}

  ~DataOpenFile() = default;

  void
  setUp() {
    m_openFileSettings.lStructSize = sizeof(m_openFileSettings);
    m_openFileSettings.nMaxFile = (m_fileName.size() - 1);

    m_openFileSettings.lpstrFile = m_fileName.data();
    m_openFileSettings.lpstrFile[0] = '\0';

    m_openFileSettings.hwndOwner = nullptr;
    m_openFileSettings.lpstrFilter = fileTypes;
    m_openFileSettings.nFilterIndex = 1;
    // save the current directory so we don't change it later
    GetCurrentDirectoryA((m_currentDirectory.size() * sizeof(char)) - 1,
                         m_currentDirectory.data());
  }

  static constexpr const char* fileTypes = "text files \0*.txt\0 All files\0*.*\0";

  OPENFILENAMEA m_openFileSettings;
  std::string m_fileName;
  std::string m_currentDirectory;
};

DataOpenFile
createDataOpenFile();

fs::path
openFilePath(BaseApp* app);

fs::path
saveFilePath(BaseApp* app);

int
createTrack(BaseApp* app);

int
closeApp(BaseApp* app);

int
loadLevelMaster(BaseApp* app,const int32 level);

int
loadLevel1(BaseApp* app);

int
loadLevel2(BaseApp* app);

int
loadLevel3(BaseApp* app);

int
loadCharacterMaster(BaseApp* app, const int32 selectedSpriteAtlas);

int
loadCharacterMario(BaseApp* app);

int
loadCharacterPeach(BaseApp* app);

int
loadCharacterBowser(BaseApp* app);

int
loadCharacterYoshi(BaseApp* app);

int
loadCharacterKong(BaseApp* app);

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
EditorApp::createLoop() {

  m_gameMap->clear();
  {
    auto& gm = GameManager::getInstance();
    auto& container = gm.getAgentContainerRef();
      for (auto& elem : container) {
        elem.getBoid().m_data.m_position = Vec2(-1337.0f, -221321321.0f);
      }
  }


  const float minimumTime = 0.18f;
  float currentTime = 0.0f;
  while (m_window->isOpen()) {

    m_timer.StartTiming();

    handleInput();

    const bool acceptInput = m_mouseData.isPressedWith(MOUSE_ACCION::kLeftButton);
    if (acceptInput && currentTime > minimumTime) {
      const FollowPathNode node(m_mouseData.m_mousePosition, 25.0f);
      m_gameMap->addNode(node);
      currentTime = 0.0f;
    }

    handleDraw();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
    currentTime += m_deltaTime;
  }

  return 0;
}

int
EditorApp::introSequence() {

  const float introSequenceLength = 3.0f;
  const float changeDelta = introSequenceLength / m_stringSequence->getSequenceSize();
  float deltaTimeSum = 0.0f;
  float timeSenceSequenceAdvancement = 0.0f;

  m_gameText->setCharacterSize(66u * 3);
  m_gameText->m_textString = m_stringSequence->getCurrentString();
  m_gameText->setPosition({ m_screenWidth / 3.0f, m_screenHeight / 3.0f });

  while (introSequenceLength > deltaTimeSum) {
    m_timer.StartTiming();
    handleDraw();

    if (timeSenceSequenceAdvancement >= changeDelta) {
      m_gameText->setString(m_stringSequence->getNextString());
      timeSenceSequenceAdvancement = 0.0f;
    }

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();
    deltaTimeSum += m_deltaTime;
    timeSenceSequenceAdvancement += m_deltaTime;
  }

  m_gameText->setString(std::string_view(" 1 / 5 "));

  return 0;
}

int
EditorApp::mainLoop() {
  auto& gameMan = GameManager::getInstance();
  gameMan.setupGroup();

  setRandomRacerSprites();

  introSequence();

  m_music->play();
  m_music->setLoop(true);
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

    std::srand(std::random_device{}());

    m_window = make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                             sf::String(" app"),
                                             sf::Style::Default);

    m_gameMap = make_unique<GameMap>();

    m_stateMachine = make_unique<UIStateMachine>();

    m_userRacer = make_unique<Racer>(Boid());

    m_userCircle = make_unique<sf::CircleShape>(30.0f);
    m_userCircle->setOutlineColor(sf::Color::Cyan);
    m_userCircle->setFillColor(sf::Color::Transparent);
    m_userCircle->setOutlineThickness(3.0f);
    m_userCircle->setPosition(m_screenWidth / 2.0f, m_screenHeight / 2.0f);
    {
      m_gameText = make_unique<UIText>();
      UITextDescriptor desc;
      desc.pathToFont = s_pathToFrontPixels;
      desc.textSize = 40u;
      desc.textFillColor = sf::Color::White;
      desc.outlineTextSize = 1.5f;
      desc.textStyle = sf::Text::Style::Regular;
      desc.textString = "Ready";
      desc.textPosition = sf::Vector2f(0.0f, 0.0f);
      m_gameText->init(desc);
    }

    {
      m_music = make_unique<sf::Music>();
      m_music->setVolume(40.0f);
      const auto musicPath = fs::path(m_initialPath).append(s_pathToMusic);
      if (!m_music->openFromFile(musicPath.generic_string())) {
        throw new std::runtime_error("can NOT load music");
        return -1;
      }
    }

    m_stringSequence = make_unique<StringSequence>(StringSequence({ "Ready","Set","Go!!!!!!" }));

    {
      const fs::path pathToAtlas = fs::path(m_initialPath).append(s_pathsToMarioSprites.m_spriteSheet);
      const fs::path pathToAtlas1 = fs::path(m_initialPath).append(s_pathsToBowserSprites.m_spriteSheet);
      const fs::path pathToAtlas2 = fs::path(m_initialPath).append(s_pathsToPeachSprites.m_spriteSheet);
      const fs::path pathToAtlas3 = fs::path(m_initialPath).append(s_pathsToYoshiSprites.m_spriteSheet);
      const fs::path pathToAtlas4 = fs::path(m_initialPath).append(s_pathsToKongSprites.m_spriteSheet);

      if (!createAtlas(pathToAtlas, s_pathsToMarioSprites.m_index)   ||
          !createAtlas(pathToAtlas1, s_pathsToBowserSprites.m_index) ||
          !createAtlas(pathToAtlas2, s_pathsToPeachSprites.m_index)  ||
          !createAtlas(pathToAtlas3, s_pathsToYoshiSprites.m_index)  ||
          !createAtlas(pathToAtlas4, s_pathsToKongSprites.m_index))
      {
        return -1;
      }
      std::sort(begin(m_spritesAtlases), end(m_spritesAtlases));
    }
    createUI();

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
EditorApp::createUI() {

  std::vector<UISceneDesc> descriptors;
  descriptors.reserve(4);

  const UISceneDesc mainMenu = createMainMenuScene();
  const UISceneDesc levelSelect = createLevelSelect();
  const UISceneDesc creditScene = createCreditScene();
  const UISceneDesc characterSelectScene = createCharacterSelectScene();

  descriptors.emplace_back(mainMenu);
  descriptors.emplace_back(levelSelect);
  descriptors.emplace_back(creditScene);
  descriptors.emplace_back(characterSelectScene);

  m_stateMachine->init(descriptors, this);
  return true;
}

UISceneDesc
EditorApp::createMainMenuScene() const {
  UISceneDesc menuScene;
  const auto halfScreenWidth = static_cast<float>(m_screenWidth) / 2u;
  const UIRectangle playRect(UIRectangleDesc(300, 200,
                             sf::Vector2f(halfScreenWidth, 300),
                             "", sf::Color::Green));

  const auto rectSize = playRect.getSize();
  const auto exitRect = UIScene::copyAndModifyFromTemplate(playRect,
                                                           sf::Color::Red,
                                                           Vec2(0.0f, rectSize.y * 1.5f));

  const auto createRect = UIScene::copyAndModifyFromTemplate(exitRect,
                                                             sf::Color::Yellow,
                                                             Vec2(rectSize.x * 1.5f),
                                                             Vec2(rectSize.x + 5.0f, rectSize.y));

  const auto creditRect = UIScene::copyAndModifyFromTemplate(exitRect,
                                                             sf::Color::Yellow,
                                                             Vec2(0.f, rectSize.y * 1.5f));

  UITextDescriptor disc;
  disc.pathToFont = s_pathToFrontPixels;
  disc.textString = " Play\n Button";
  disc.textFillColor = sf::Color::Black;
  disc.textOuterColor = sf::Color::Blue;
  disc.textSize = 60;
  disc.textStyle = sf::Text::Bold;

  menuScene.AddElement(playRect, s_levelSelectID, []() {}, disc);

  disc.textString = " Exit\n Button";
  menuScene.AddElement(exitRect, UIScene::NOMORE_SCENES_ID, closeApp, disc);

  disc.textString = " Create\n Track";
  menuScene.AddElement(createRect, UIScene::NOMORE_SCENES_ID, createTrack, disc);

  disc.textString = " Credits";
  menuScene.AddElement(creditRect, s_creditID, []() {}, disc);

  menuScene.ID = s_startMenuID;
  return  menuScene;
}

UISceneDesc
EditorApp::createLevelSelect() const {

  const auto halfScreenWidth = static_cast<float>(m_screenWidth) / 2u;
  UISceneDesc levelSelect;
  const UIRectangle level1Rect(UIRectangleDesc(300, 200,
                               sf::Vector2f(halfScreenWidth, 300),
                               "", sf::Color::Yellow));

  const auto rectSize = level1Rect.getSize();

  const auto level2Rect = UIScene::copyAndModifyFromTemplate(level1Rect,
                                                             std::nullopt,
                                                             Vec2(0.0f, rectSize.y * 1.5f));

  const auto level3Rect = UIScene::copyAndModifyFromTemplate(level2Rect,
                                                             std::nullopt,
                                                             Vec2(0.0f, rectSize.y * 1.5f));

  UITextDescriptor disc;
  disc.pathToFont = s_pathToFrontPixels;
  disc.textString = " LEVEL 1 ";
  disc.textFillColor = sf::Color::Black;
  disc.textOuterColor = sf::Color::Blue;
  disc.textStyle = sf::Text::Bold;
  disc.textSize = 60;

  const auto nextSceneID = s_characterSelectID;

  levelSelect.AddElement(level1Rect, nextSceneID, loadLevel1, disc);

  disc.textString = " LEVEL 2 ";
  levelSelect.AddElement(level2Rect, nextSceneID, loadLevel2, disc);

  disc.textString = " LEVEL 3 ";
  levelSelect.AddElement(level3Rect, nextSceneID, loadLevel3, disc);
  levelSelect.ID = s_levelSelectID;

  return levelSelect;
}

UISceneDesc
EditorApp::createCreditScene() const {
  UISceneDesc creditScene;
  {
    UISceneDesc::TextElement element;

    element.index = UISceneDesc::TextElement::INVALID_INDEX;
    UITextDescriptor textDisc;
    textDisc.pathToFont = s_pathToFrontDisco;
    textDisc.textFillColor = sf::Color::White;
    textDisc.textSize = 60u;
    std::string path = fs::path(m_initialPath).append(s_pathToCredits).generic_string();
    textDisc.textString = util::loadFileToString(path);

    UIText newTextObject;
    newTextObject.init(textDisc);

    element.text.takeResources(std::move(newTextObject));
    creditScene.texts.emplace_back(element);
  }
  creditScene.ID = s_creditID;
  const sf::Vector2f position(m_screenWidth - 300, m_screenHeight);

  const UIRectangleDesc exitRect(800, 400, position, "", sf::Color::Red);

  UITextDescriptor textDisc;
  textDisc.pathToFont = s_pathToFrontDisco;
  textDisc.textFillColor = sf::Color::White;
  textDisc.textSize = 62u;
  textDisc.textString = "<=======\nGo back";

  creditScene.AddElement(UIRectangle(exitRect), s_startMenuID, []() {}, textDisc);

  return creditScene;
}

UISceneDesc
EditorApp::createCharacterSelectScene() const {
  UISceneDesc characterSelectScene;
  {
    const auto oneThirdOfScreen = m_screenWidth / 3u;
    const UIRectangleDesc marioRectangle(200,
                                         200,
                                         sf::Vector2f(oneThirdOfScreen, m_screenHeight / 2.0f),
                                         s_pathsToMarioSprites.m_portriat);

    const sf::Vector2f rectangleDelta = sf::Vector2f(marioRectangle.width * 1.5f, 0.f);

    const UIRectangleDesc peachRectangle(200,
                                         200,
                                         marioRectangle.position + rectangleDelta,
                                         s_pathsToPeachSprites.m_portriat);


    const UIRectangleDesc kongRectangle(200,
                                        200,
                                        peachRectangle.position + rectangleDelta,
                                        s_pathsToKongSprites.m_portriat);

    const UIRectangleDesc yoshiRectangle(200,
                                         200,
                                         kongRectangle.position + rectangleDelta,
                                         s_pathsToYoshiSprites.m_portriat);

    characterSelectScene.AddElement(UIRectangle(marioRectangle),
                                    UIScene::NOMORE_SCENES_ID,
                                    loadCharacterMario);

    characterSelectScene.AddElement(UIRectangle(peachRectangle),
                                    UIScene::NOMORE_SCENES_ID,
                                    loadCharacterPeach);

    characterSelectScene.AddElement(UIRectangle(kongRectangle),
                                    UIScene::NOMORE_SCENES_ID,
                                    loadCharacterKong);

    characterSelectScene.AddElement(UIRectangle(yoshiRectangle),
                                    UIScene::NOMORE_SCENES_ID,
                                    loadCharacterYoshi);
  }
  characterSelectScene.ID = s_characterSelectID;
  return characterSelectScene;
}




RESULT_APP_STAGES::E
EditorApp::handleDraw() {
  m_window->clear();

  auto& gm = GameManager::getInstance();
  auto& containter = gm.getAgentContainerRef();
  m_gameMap->draw(*m_window);
  gm.drawRacers(*m_window);
  {
    const auto boidData = containter.back().getBoidData();
    const auto bounds = boidData.m_shape.getGlobalBounds();
    const sf::Vector2f position(bounds.left - (bounds.width / 2),
                                bounds.top - (bounds.height / 2));
    m_userCircle->setPosition(position.x, position.y);
    m_window->draw(*m_userCircle);
    m_gameText->draw(m_window.get());
  }

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
        //const auto path = fs::path(m_initialPath).append(s_pathToSaveFileDefault);
        //m_gameMap->saveMap(path.generic_string());
        saveFilePath(this);
      }
      break;
      case sf::Keyboard::L:
      {
        const auto path = openFilePath(this);
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
EditorApp::createAtlas(const std::filesystem::path& pathToAtlas,
                       const uint64 index) {

  const std::vector<sf::IntRect> rectSequence =
    util::createHorizontalIntRectSequence(sf::Vector2i(0, 30), sf::Vector2i(30, 30), 12);

  const std::vector<RotationSegment> rotations =
    util::createRotationSegmentSequence(gvar::halfPi,
                                        gvar::halfPi - gvar::pi,
                                        12);

  const SpriteAtlasDesc desc(pathToAtlas, rectSequence, rotations, index);

  SpriteAtlas newAtlas;

  const bool isAtlasInitialized = newAtlas.init(desc);

  if (isAtlasInitialized) {
    m_spritesAtlases.push_back(newAtlas);

    auto& ref = m_spritesAtlases.back();
    const sf::Color backGroundColor = ref.getColorOfPixel(0u, 0u);
    ref.makeColorTransparent(backGroundColor);
  }

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

void
EditorApp::setRacerSprites(const uint64 selectedRacer,
                           const uint64 selectedSpriteAtlas) {
  assert(selectedSpriteAtlas <= m_spritesAtlases.size() - 1);

  auto& gameMan = GameManager::getInstance();
  auto& container = gameMan.getAgentContainerRef();
  const uint64 limit = container.size() - 1;
  if (selectedRacer <= limit) {
    const auto findSpriteAtlas = [selectedSpriteAtlas](const SpriteAtlas& atlas) {
      return atlas.getIndex() == selectedSpriteAtlas;
    };

    auto iter = std::find_if(begin(m_spritesAtlases), end(m_spritesAtlases), findSpriteAtlas);
    assert(iter != end(m_spritesAtlases));
    container[selectedRacer].m_atlasPtr = &(*iter);
  }

}

void
EditorApp::setRandomRacerSprites(const bool force)
{
  auto& container = GameManager::getInstance().getAgentContainerRef();
  const uint64 limit = m_spritesAtlases.size() - 1u;
  std::uniform_int_distribution dist(static_cast<uint64>(0), limit);
  std::ranlux48 randEngine(std::random_device{}());

  for (auto& elem : container) {
    if (nullptr == elem.m_atlasPtr || true == force) {
      elem.m_atlasPtr = &m_spritesAtlases[dist(randEngine)];
    }
  }
}

bool
EditorApp::saveCurrentMap(const std::string_view path) const {
  return m_gameMap->saveMap(path);
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

  {
    const BoidDescriptor followBoid = Boid::createFollowPathBoidDescriptor
    (m_gameMap->m_positionData,
     Vec2((11 * 35), 500),
     0.80f + util::randomRangeFloat(0.65f, 1.2f)
    );
    *m_userRacer = Racer(followBoid);
    gameMan.addRacerToGame(*m_userRacer);

  }

  return true;
}


DataOpenFile
createDataOpenFile() {
  DataOpenFile fileSettings;

  /**
   * All text before the first null character is the name we give to the type
   * of files we are looking for what comes after that is the name of the extension
   */
  static constexpr const char* fileTypes = "All files\0*.*\0 \0*.txt\0";

  fileSettings.m_openFileSettings.lStructSize = sizeof(fileSettings.m_openFileSettings);
  fileSettings.m_openFileSettings.hwndOwner = nullptr;

  fileSettings.setUp();
  return fileSettings;
}

fs::path
openFilePath(BaseApp* app) {

  assert(app != nullptr);
  auto editorApp = dynamic_cast<EditorApp*> (app);

  auto fileSetting = createDataOpenFile();
  fileSetting.setUp();
  GetOpenFileNameA(&fileSetting.m_openFileSettings);

  const fs::path result = fileSetting.m_fileName;
  editorApp->createPath(fs::path(result));

  SetCurrentDirectoryA(fileSetting.m_currentDirectory.data());
  return result;
}

fs::path
saveFilePath(BaseApp* app) {
  assert(app != nullptr);
  auto editorApp = dynamic_cast<EditorApp*> (app);

  auto fileSetting = createDataOpenFile();
  fileSetting.setUp();
  GetSaveFileNameA(&fileSetting.m_openFileSettings);

  if (std::string::npos == fileSetting.m_fileName.rfind(".txt")) {
    const auto firstNull = fileSetting.m_fileName.find('\0');
    fileSetting.m_fileName.insert(firstNull, ".txt");
  }

  const fs::path result = fileSetting.m_fileName;
  editorApp->saveCurrentMap(fileSetting.m_fileName);

  SetCurrentDirectoryA(fileSetting.m_currentDirectory.data());
  return result;
}


int
createTrack(BaseApp* app) {
  assert(nullptr != app);
  auto gameApp = reinterpret_cast<EditorApp*>(app);
  return gameApp->createLoop();
}


int
closeApp(BaseApp* app) {
  app->closeWindow();
  return 0;
}

int
loadLevelMaster(BaseApp* app, const int32 level) {
  assert(nullptr != app);
  auto gameApp = reinterpret_cast<EditorApp*>(app);
  switch (level) {
  case 1:
  gameApp->createPath(s_pathToLevel1);
  break;

  case 2:
  gameApp->createPath(s_pathToLevel2);
  break;

  case 3:
  gameApp->createPath(s_pathToLevel3);
  break;

  default:
  return -1;
  break;
  }

  return 0;
}


int
loadLevel1(BaseApp* app) {
  return loadLevelMaster(app, 1);
}


int
loadLevel2(BaseApp* app) {
  return loadLevelMaster(app, 2);
}

int
loadLevel3(BaseApp* app) {
  return loadLevelMaster(app, 3);
}

int
loadCharacterMaster(BaseApp* app,
                    const int64 selectedSpriteAtlas) {
  auto& container = GameManager::getInstance().getAgentContainerRef();
  auto gameApp = reinterpret_cast<EditorApp*>(app);
  gameApp->setRacerSprites(container.size() - 1,
                           selectedSpriteAtlas);

  return 0;
}


int
loadCharacterMario(BaseApp* app) {
  return loadCharacterMaster(app, s_pathsToMarioSprites.m_index);
}

int
loadCharacterPeach(BaseApp* app) {
  return loadCharacterMaster(app, s_pathsToPeachSprites.m_index);
}

int
loadCharacterBowser(BaseApp* app) {
  return loadCharacterMaster(app, s_pathsToBowserSprites.m_index);
}

int
loadCharacterYoshi(BaseApp* app) {
  return loadCharacterMaster(app, s_pathsToYoshiSprites.m_index);
}

int
loadCharacterKong(BaseApp* app) {
  return loadCharacterMaster(app, s_pathsToKongSprites.m_index);
}


