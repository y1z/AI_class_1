#pragma once
#include <memory> // std::unique_ptr
#include <filesystem> // std::filesystem::path
#include "BaseApp.h"

/**
 * Is an editor for manipulating AI agents (Boids)
 */
class EditorApp : public BaseApp
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
  int
  mainLoop()override;

  int
  init();

 private:
  std::filesystem::path m_path;
  std::unique_ptr<sf::RenderWindow> m_window;
  std::string m_file;

};

