#pragma once
#include <memory> // std::unique_ptr
#include <filesystem> // std::filesystem::path
#include "BaseApp.h"
#include "SpriteAtlas.h"
#include "GameMap.h"
#include "UIStateMachine.h"
#include "MouseData.h"


namespace RESULT_APP_STAGES {
  enum E {
  kERROR = -1,
  kNO_ERROR = 0,
  kMISSING_IMPL,
};
}

/**
 * Is an editor for manipulating AI agents (Boids)
 */
class EditorApp final : public BaseApp
{

 public:
  EditorApp();
  EditorApp(const EditorApp& other) = delete;
  EditorApp(EditorApp&& other) noexcept = delete;
  ~EditorApp() = default;

  EditorApp&
  operator=(const EditorApp& other) = delete;

  EditorApp&
  operator=(EditorApp&& other) noexcept = delete;


  /**
   * Runs the app.
   */
  int
  run(unsigned int screenWidth,
      unsigned int screenHeight) override;

  /**
   * Closes the window
   */
  void
  closeWindow() override;

  /**
   * Used for creating custom tracks.
   */
  int
  createLoop();

 protected:
  /**
   * The main process of the Game
   */
  int
  mainLoop()override;

  /**
   * creates the main menu.
   */
  int
  menuLoop();


  /**
   * For creation of resources
   */
  int
  init();

  /**
   * for creating all the UI of the Game
   */
  bool
  createUI();

  /**
   * Creates the descriptor for the UIScene.
   */
  UISceneDesc
  createMainMenuScene()const;

  /**
   * Creates the level select scene.
   */
  UISceneDesc
  createLevelSelect()const;

  /**
   * Creates the scene that contains credits.
   */
  UISceneDesc
  createCreditScene()const;


  UISceneDesc
  createCharacterSelectScene()const;

  /**
   * handles drawing all relevant entity's .
   */
  RESULT_APP_STAGES::E
  handleDraw();

  /**
   * Handles the input of the user.
   */
  RESULT_APP_STAGES::E
  handleInput();

  /**
   * The update logic for the racers is here.
   */
  RESULT_APP_STAGES::E
  handleRacers();

  /**
   * @brief creates a sprite atlas for the characters of the game.
   */
  bool
  createAtlas(const std::filesystem::path& pathToAtlas);

public:
  /**
   * @brief creates the path the agents of the are going to follow.
   */
  void
  createPath(const std::filesystem::path& pathToFile = "");

  /**
   * @brief sets up the path for all the boids of the game.
   */
  void
  setUpNewPath();

  /**
   * @brief Give the racers there own sprites.
   */
  void
  setRacerSprites(const uint64 selectedRacer,
                  const uint64 selectedSpriteAtlas);

  /**
   * @brief Gives every Racer a random sprite IF they are not already using one.
   */
  void
  setRandomRacerSprites(const bool force = false);

private:
  /**
   * @brief creates the racers a.k.a the agents of the game.
   */
  bool
  createRacer();


 private:
  const std::filesystem::path m_initialPath = std::filesystem::current_path();
  /** Contains all the sprites atlases for each character. */
  std::deque< SpriteAtlas > m_spritesAtlases;

  MouseData m_mouseData; /**< Contains all relevant data of the mouse.*/
  /** The racer the user selected. */
  std::unique_ptr<Racer> m_userRacer;
  std::unique_ptr<sf::RenderWindow> m_window;/**< Whats being rendered. */
  std::unique_ptr<GameMap> m_gameMap;/**< Contains the map used. */
  std::unique_ptr<UIStateMachine> m_stateMachine; /**< Controls the UI. */
  /**
   * Used for highlighting the user Boid
   */
  std::unique_ptr<sf::CircleShape> m_userCirle;
};

