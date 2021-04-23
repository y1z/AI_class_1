#pragma once
#include "BaseApp.h"
#include <memory> // std::unique_ptr
#include <filesystem> // std::filesystem::path
#include <SFML/Audio/Music.hpp> // for sf::Music

#include "SpriteAtlas.h"
#include "GameMap.h"
#include "UIStateMachine.h"
#include "MouseData.h"
#include "StringSequence.h"
#include "SoundPlayer.h"


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
   * The intro sequence to the level
   */
  int
  introSequence();


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
   * Creates all the character sprites.
   */
  bool
  createCharacterSprites();

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

  /**
   * Creates the character select scene.
   */
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
   * Updates the logic for keeping track of the counters for the first place racer.
   */
  RESULT_APP_STAGES::E
  handleCounter();

  /**
   * @brief creates a sprite atlas for the characters of the game.
   */
  bool
  createAtlas(const std::filesystem::path& pathToAtlas,
              const uint64 index);

  /**
   * @returns
   *  A reference to the racer in first place.
   */
  const Racer&
  getRacerInFirstPlace()const;

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

  /**
   * @brief Save the current map
   */
  bool
  saveCurrentMap(const std::string_view path)const;

 private:
  /**
   * @brief creates the racers a.k.a the agents of the game.
   */
  bool
  createRacers();

  /**
   * Used for keeping track of the original path the application started with.
   */
  const std::filesystem::path m_initialPath = std::filesystem::current_path();

  /**
   * Contains all the sprites atlases for each character.
   */
  std::deque< SpriteAtlas > m_spritesAtlases;

  /**
   * Contains all relevant data of the mouse.
   */
  MouseData m_mouseData;


  /** The racer the user selected. */
  std::unique_ptr<Racer> m_userRacer;

  /** Whats being rendered. */
  std::unique_ptr<sf::RenderWindow> m_window;

  /** Contains the map used. */
  std::unique_ptr<GameMap> m_gameMap;

  /** Controls the UI. */
  std::unique_ptr<UIStateMachine> m_stateMachine;

  /**
   * Used for highlighting the user Boid
   */
  std::unique_ptr<sf::CircleShape> m_userCircle;

  /**
   * Used for playing music
   */
  std::unique_ptr<sf::Music> m_music;

  /**
   * Used for playing sounds
   */
  std::unique_ptr < SoundPlayer > m_soundPlayer;

  /**
   * Used for all text during the game.
   */
  std::unique_ptr<UIText> m_gameText;

  /**
   * Contains a sequence of strings to be used in the game.
   */
  std::unique_ptr< StringSequence > m_stringSequence;

  /**
   * Controls how many laps are done util the race ends.
   */
  uint16 m_lapLimit = 3;

};

