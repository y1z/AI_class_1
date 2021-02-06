#pragma once
#include "BaseApp.h"

#include <memory>

/**
* @brief Defines an app used to test the Boids.
*/
class TestBoidApp final : public BaseApp
{
public:
  TestBoidApp() = default;
  TestBoidApp(const TestBoidApp&) = delete;
  TestBoidApp(TestBoidApp&&) = delete;
  ~TestBoidApp() = default;
public:
  TestBoidApp& operator=(const TestBoidApp&) = delete;
  TestBoidApp& operator=(TestBoidApp&&) = delete;
public:
  
  int
  run(unsigned int screenWith,
      unsigned int screenHeight) override;
 
private:

  /**
  * @brief Initializes all the variables used by the app.
  * @bug no known bugs.
  */
  int 
  init();

  /**
  * @brief Takes care of handling user input.
  * @bug no known bugs.
  */
  void 
  handleInput();

  /**
  * @brief Takes care of all boid related operations.
  * @bug no known bugs.
  */
  void
  handleBoids();


  /**
  * @brief Takes care of everything related with drawing on the screen.
  * @bug no known bugs.
  */
  void
  handleRendering();

  /**
  * @brief Contains the main Loop of the app.
  * @bug no known bugs.
  */
  int
  mainLoop()override;
  
private:

  /** @brief controls the mouse position. */
  std::unique_ptr<Boid> m_mousePosition;

  /** @brief is where the window is drawn. */
  std::unique_ptr<sf::RenderWindow> m_window;
};

