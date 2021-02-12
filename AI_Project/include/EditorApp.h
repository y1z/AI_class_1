#pragma once
#include <memory> // std::unique_ptr
#include <filesystem> // std::filesystem::path
#include "BaseApp.h"

namespace RESULT_APP_STAGES {
  enum E {
    kERROR = -1,
    NO_ERROR = 0, 
    MISSING_IMPL, 
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


  RESULT_APP_STAGES::E
  handleDraw();

  RESULT_APP_STAGES::E
  handleInput();

  /**
   * The update logic for the racers is here.
   */
  RESULT_APP_STAGES::E
  handleRacers();


 private:
  std::filesystem::path m_path;
  std::string m_file;
  std::unique_ptr<sf::RenderWindow> m_window;

  Vec2 m_mousePos;

};

