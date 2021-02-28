#pragma once
#include <memory> // std::unique_ptr
#include <filesystem> // std::filesystem::path
#include "BaseApp.h"
#include "SpriteAtlas.h"
#include "GameMap.h"
#include "UIStateMachine.h"


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


 protected:
   /**
    * The main process of the Game
    */
  int
  mainLoop()override;

  /**
   * For creation of resources
   */
  int
  init();

  bool
  createMenu();

  RESULT_APP_STAGES::E
  handleDraw();

  RESULT_APP_STAGES::E
  handleInput();

  /**
   * The update logic for the racers is here.
   */
  RESULT_APP_STAGES::E
  handleRacers();

  bool
  createAtlas(const std::filesystem::path& pathToAtlas) const;

  void
  createPath(const std::filesystem::path& pathToFile = "");

  bool
  createRacer();


 private:
  const std::filesystem::path m_initialPath = std::filesystem::current_path();

  std::unique_ptr<sf::RenderWindow> m_window;/**< Whats being rendered */
  std::unique_ptr<SpriteAtlas> m_spriteAtlas; /**< Controls the sprites.*/
  std::unique_ptr<GameMap> m_gameMap;
  std::unique_ptr<UIStateMachine> m_stateMachine;
  Vec2 m_mousePos;
};

