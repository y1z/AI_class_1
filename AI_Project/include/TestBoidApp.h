#pragma once
#include "BaseApp.h"
#include "Boid.h"

#include <memory>

/**
* @brief Defines an app used to test the Boids.
*/
class TestBoidApp final : public BaseApp
{
public:
  
  int
  run() override;
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
  * @brief 
  * @bug no known bugs.
  */
  void
  handleBoids();

  /**
  * @brief Contains the main Loop of the app.
  * @bug no known bugs.
  */
  int
  mainLoop();
  
private:
  std::unique_ptr<Boid> m_boid;
  std::unique_ptr<sf::RenderWindow> m_window;
  Vec2 m_mousePosition;

};

