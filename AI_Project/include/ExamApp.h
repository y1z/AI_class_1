#pragma once

#include "BaseApp.h"
#include "UiManager.h"



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

  void
  handleInput();

  void
  handleBoid();


  void
  handleDraw();

  int
  mainLoop() override;

private:

  /** @brief controls the UI*/
  UiManager m_manager; 

  /** @brief is where the window is drawn. */
  std::unique_ptr<sf::RenderWindow> m_window;

  std::unique_ptr<Boid> m_mousePos;

  std::filesystem::path m_path;
};

