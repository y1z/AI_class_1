#pragma once

#include "BaseApp.h"
#include "UiManager.h"
#include "SpriteAtlas.h"


class ExamApp : public BaseApp 
{
public:
  ExamApp();
  ExamApp(const ExamApp&) = delete;
  ExamApp(ExamApp&&) = default;
  ~ExamApp() = default;

  int
  run() override;


protected:

  int
  init(unsigned int width,
       unsigned int height);

  
  bool
  createRacers()const;

  void
  createPath()const;

  bool
  createAtlas(const std::filesystem::path& pathToAtlas)const;
  

  void
  handleInput();

  void
  handleRacers();

  void
  handleDraw();

  int
  mainLoop() override;

private:

  /** @brief controls the UI*/
  UiManager m_manager; 

  /** @brief is where the window is drawn. */
  std::unique_ptr<sf::RenderWindow> m_window;

  std::unique_ptr<SpriteAtlas> m_atlas;

  std::unique_ptr<Boid> m_mousePos;

  std::filesystem::path m_path;
};

